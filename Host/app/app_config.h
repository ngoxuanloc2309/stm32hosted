#ifndef __APP_CONFIG_H
#define __APP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define USR_SPI_CS_GPIO_Port            GPIOB
#define USR_SPI_CS_Pin                  GPIO_PIN_1
#define SCK_PORT                        GPIOA
#define SCK_PIN                         GPIO_PIN_5
#define MISO_PORT                       GPIOA
#define MISO_PIN                        GPIO_PIN_6
#define MOSI_PORT                       GPIOD
#define MOSI_PIN                        GPIO_PIN_7
#define GPIO_HANDSHAKE_GPIO_Port        GPIOD           //EXTI Rising mode
#define GPIO_HANDSHAKE_Pin              GPIO_PIN_10     //EXTI Rising mode
#define GPIO_DATA_READY_GPIO_Port       GPIOD
#define GPIO_DATA_READY_Pin             GPIO_PIN_11

/*  WiFi Credentials ─ */
#define WIFI_SSID                   "Spotdog123"
#define WIFI_PASSWORD               "123456789"

/*  MQTT Broker  */
#define MQTT_BROKER_HOST            "broker.hivemq.com"
#define MQTT_BROKER_PORT            1883
#define MQTT_CLIENT_ID              "claude01"
#define MQTT_KEEPALIVE_SEC          60
#define MQTT_TIMEOUT_MS             5000

/*  MQTT Topics  */
#define MQTT_TOPIC_PUBLISH          "synaptix/test/pub"
#define MQTT_TOPIC_SUBSCRIBE        "synaptix/test/sub"

/*  UART Log  */
#define LOG_UART                    huart3

/*  FreeRTOS Task Config  */
#define SPI_TASK_STACK_SIZE         4096
#define SPI_TASK_PRIORITY           7
#define MQTT_TASK_STACK_SIZE        4096
#define MQTT_TASK_PRIORITY          5

#define ESP_NETIF_MAC   { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 }
#define ESP_NETIF_IP        "192.168.1.100"
#define ESP_NETIF_GW        "192.168.1.1"
#define ESP_NETIF_MASK      "255.255.255.0"

#ifdef __cplusplus
}
#endif

#endif /* __APP_CONFIG_H */