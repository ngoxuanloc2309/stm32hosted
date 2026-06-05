Hiện tại tôi đang cố gắng port esp hosted vào prj của tôi tuy nhiên ở example đang dùng esp32 giao tiếp với nhau mà giờ tôi muốn dùng stm32 để thay thế. Tuy nhiên nó bị vướng 1 vài cái thư viện gốc của esp idf như: "In file included from Host/lib/esp-hosted-mcu/host/api/src/esp_hosted_api.c:12:                                                                                           
Host/lib/esp-hosted-mcu/host/api/include/esp_hosted_transport_config.h:12:10: fatal error: esp_err.h: No such file or directory                                           
   12 | #include "esp_err.h"                                                                                                                                              
      |          ^~~~~~~~~~~                                                                                                                                              
compilation terminated.
make: *** [Makefile:210: build/esp_hosted_api.o] Error 1

D:\Synaptix\SynaptiX\esp32_stm32\host_newgen>" ;;;; "PS D:\Synaptix\SynaptiX\esp32_stm32> Get-ChildItem -Recurse -Include "esp_err.h","esp_log.h","esp_check.h","esp_idf_version.h","esp_mac.h","esp_task.h" "D:\esp_idf\v5.4.3\esp-idf\components" | Select-Object FullName

FullName                                                                 
--------                                                                 
D:\esp_idf\v5.4.3\esp-idf\components\esp_common\include\esp_check.h      
D:\esp_idf\v5.4.3\esp-idf\components\esp_common\include\esp_err.h        
D:\esp_idf\v5.4.3\esp-idf\components\esp_common\include\esp_idf_version.h
D:\esp_idf\v5.4.3\esp-idf\components\esp_hw_support\include\esp_mac.h    
D:\esp_idf\v5.4.3\esp-idf\components\esp_system\include\esp_task.h       
D:\esp_idf\v5.4.3\esp-idf\components\log\include\esp_log.h    " . Nên tôi nghĩ ra 1 cách là viết 1 layer là stubheader ở Host/stub_header (tuy nhiên tôi chưa viết gì cả)