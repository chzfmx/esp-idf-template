#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "wifi_net.h"
#include "led.h"
#include "button.h"
#include "udp_server.h"

#define TAG 		"[app_main]"

void app_main(void)
{
    nvs_flash_init();
	/*
    tcpip_adapter_init();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    wifi_config_t sta_config = {
        .sta = {
            .ssid = "hompe-wifi",
            .password = "Hompe@0321",
            .bssid_set = false
        }
    };
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_ERROR_CHECK( esp_wifi_connect() );
    */
    ESP_LOGI(TAG, "Create vWifi_Task...");
	xTaskCreate(vWifi_Task, WIFI_TASK_NAME, WIFI_TASK_STACK_SIZE, NULL, WIFI_TASK_PRIORITY, NULL);
	ESP_LOGI(TAG, "Create vLed_Task...");
	xTaskCreate(vLed_Task, LED_TASK_NAME, LED_TASK_STACK_SIZE, NULL, LED_TASK_PRIORITY, NULL);
	ESP_LOGI(TAG, "Create vButton_Task...");
	xTaskCreate(vButton_Task,BUTTON_TASK_NAME,BUTTON_TASK_STACK_SIZE,NULL,BUTTON_TASK_PRIORITY,NULL);
	vTaskDelay(15000 / portTICK_PERIOD_MS);
	ESP_LOGI(TAG, "Create vUdpServer_Task...");
	xTaskCreate(vUdpServer_Task,UDPSERVER_TASK_NAME,UDPSERVER_TASK_STACK_SIZE,NULL,UDPSERVER_TASK_PRIORITY,NULL);
    while (true) {
		//printf("app_main: running......\r\n");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

