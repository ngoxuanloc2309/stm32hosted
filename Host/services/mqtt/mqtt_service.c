#include <string.h>
#include "mqtt_service.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "FreeRTOS.h"
#include "task.h"

#define MQTT_NETWORK_BUFFER_SIZE    2048
#define MQTT_SEND_TIMEOUT_MS        5000

struct NetworkContext {
    int socket;
};

typedef struct {
    const char      *topic;
    uint8_t          qos;
    mqtt_callback_t  cb;
} subscription_t;

#define MAX_SUBSCRIPTIONS   8

static MQTTContext_t        mqtt_ctx;
static NetworkContext_t     net_ctx;
static MQTTFixedBuffer_t    fixed_buf;
static uint8_t              mqtt_buf[MQTT_NETWORK_BUFFER_SIZE];
static int                  mqtt_connected = 0;
static subscription_t       subs[MAX_SUBSCRIPTIONS];
static uint8_t              sub_count      = 0;
static uint16_t             packet_id      = 1;

/* ==== Transport ==== */
static int32_t mqtt_transport_recv(NetworkContext_t *ctx, void *buf, size_t len)
{
    int32_t ret = recv(ctx->socket, buf, len, MSG_DONTWAIT);
    if (ret < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return 0;
        return -1;
    }
    return ret;
}

static int32_t mqtt_transport_send(NetworkContext_t *ctx, const void *buf, size_t len)
{
    int32_t ret = send(ctx->socket, buf, len, 0);
    return (ret < 0) ? -1 : ret;
}

/* ==== Time ==== */
static uint32_t get_time_ms(void)
{
    return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

/* ==== Event Callback ==== */
static bool mqtt_event_cb(MQTTContext_t *ctx,
        MQTTPacketInfo_t *packet,
        MQTTDeserializedInfo_t *info,
        MQTTSuccessFailReasonCode_t *reason,
        MQTTPropBuilder_t *send_props,
        MQTTPropBuilder_t *get_props)
{
    (void)ctx; (void)reason; (void)send_props; (void)get_props;

    if (packet->type != MQTT_PACKET_TYPE_PUBLISH)
        return true;

    MQTTPublishInfo_t *pub = info->pPublishInfo;
    for (uint8_t i = 0; i < sub_count; i++) {
        if (strncmp(subs[i].topic, pub->pTopicName, pub->topicNameLength) == 0) {
            if (subs[i].cb)
                subs[i].cb(subs[i].topic,
                        (const uint8_t *)pub->pPayload,
                        (uint16_t)pub->payloadLength);
        }
    }
    return true;
}

/* ==== Public API ==== */
int mqtt_service_init(void)
{
    TransportInterface_t transport = {
        .recv            = mqtt_transport_recv,
        .send            = mqtt_transport_send,
        .pNetworkContext = &net_ctx,
        .writev          = NULL,
    };

    fixed_buf.pBuffer = mqtt_buf;
    fixed_buf.size    = MQTT_NETWORK_BUFFER_SIZE;
    net_ctx.socket    = -1;
    sub_count         = 0;
    mqtt_connected    = 0;

    MQTTStatus_t status = MQTT_Init(&mqtt_ctx, &transport,
            get_time_ms, mqtt_event_cb, &fixed_buf);

    return (status == MQTTSuccess) ? 0 : -1;
}

int mqtt_service_connect(void)
{
    struct addrinfo hints = {0};
    struct addrinfo *res  = NULL;
    char port_str[8];

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    snprintf(port_str, sizeof(port_str), "%d", MQTT_BROKER_PORT);

    if (getaddrinfo(MQTT_BROKER_HOST, port_str, &hints, &res) != 0) {
        printf("mqtt: DNS failed\r\n");
        return -1;
    }

    net_ctx.socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (net_ctx.socket < 0) {
        freeaddrinfo(res);
        printf("mqtt: socket failed\r\n");
        return -1;
    }

    struct timeval tv = { .tv_sec = MQTT_SEND_TIMEOUT_MS / 1000, .tv_usec = 0 };
    setsockopt(net_ctx.socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(net_ctx.socket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    if (connect(net_ctx.socket, res->ai_addr, res->ai_addrlen) != 0) {
        freeaddrinfo(res);
        close(net_ctx.socket);
        net_ctx.socket = -1;
        printf("mqtt: TCP connect failed\r\n");
        return -1;
    }
    freeaddrinfo(res);

    MQTTConnectInfo_t conn_info              = {0};
    conn_info.cleanSession                   = true;
    conn_info.pClientIdentifier              = MQTT_CLIENT_ID;
    conn_info.clientIdentifierLength         = strlen(MQTT_CLIENT_ID);
    conn_info.keepAliveSeconds               = MQTT_KEEPALIVE_SEC;

    bool session_present = false;
    MQTTStatus_t status = MQTT_Connect(&mqtt_ctx, &conn_info,
            NULL, MQTT_TIMEOUT_MS, &session_present, NULL, NULL);

    if (status != MQTTSuccess) {
        close(net_ctx.socket);
        net_ctx.socket = -1;
        printf("mqtt: MQTT_Connect failed %d\r\n", status);
        return -1;
    }

    mqtt_connected = 1;
    printf("mqtt: connected to %s\r\n", MQTT_BROKER_HOST);
    return 0;
}

void mqtt_service_disconnect(void)
{
    if (mqtt_connected)
        MQTT_Disconnect(&mqtt_ctx, NULL, NULL);

    if (net_ctx.socket >= 0) {
        close(net_ctx.socket);
        net_ctx.socket = -1;
    }
    mqtt_connected = 0;
}

int mqtt_service_publish(const char *topic, const uint8_t *payload,
        uint16_t len, uint8_t qos)
{
    if (!mqtt_connected)
        return -1;

    MQTTPublishInfo_t pub    = {0};
    pub.qos                  = (MQTTQoS_t)qos;
    pub.pTopicName           = topic;
    pub.topicNameLength      = strlen(topic);
    pub.pPayload             = payload;
    pub.payloadLength        = len;

    MQTTStatus_t status = MQTT_Publish(&mqtt_ctx, &pub,
            (qos > 0) ? packet_id++ : 0, NULL);

    return (status == MQTTSuccess) ? 0 : -1;
}

int mqtt_service_subscribe(const char *topic, uint8_t qos, mqtt_callback_t cb)
{
    if (!mqtt_connected || sub_count >= MAX_SUBSCRIPTIONS)
        return -1;

    MQTTSubscribeInfo_t sub_info    = {0};
    sub_info.qos                    = (MQTTQoS_t)qos;
    sub_info.pTopicFilter           = topic;
    sub_info.topicFilterLength      = strlen(topic);

    MQTTStatus_t status = MQTT_Subscribe(&mqtt_ctx, &sub_info,
            1, packet_id++, NULL);

    if (status != MQTTSuccess)
        return -1;

    subs[sub_count].topic = topic;
    subs[sub_count].qos   = qos;
    subs[sub_count].cb    = cb;
    sub_count++;

    return 0;
}

void mqtt_service_process(void)
{
    if (!mqtt_connected)
        return;
    MQTT_ProcessLoop(&mqtt_ctx);
}

int mqtt_service_is_connected(void)
{
    return mqtt_connected;
}