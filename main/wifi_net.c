#include "wifi_net.h"
#include "tcp_client.h"

#define TAG				"[vWifi_Task]"


esp_err_t event_handler(void * ctx, system_event_t * event)
{
	switch(event->event_id)
	{
		case SYSTEM_EVENT_STA_START:
			ESP_LOGI(TAG, "Connecting to AP...");
			esp_wifi_connect();
		break;
		case SYSTEM_EVENT_STA_GOT_IP:
			ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
		break;
		case SYSTEM_EVENT_STA_DISCONNECTED:
			ESP_LOGI(TAG, "Wifi disconnected, try to coneect again...");
			esp_wifi_connect();
		break;
		case SYSTEM_EVENT_AP_STACONNECTED:		//有STA连接到ESP Soft-Ap
			ESP_LOGI(TAG, "station:"MACSTR" join, AID=%d",
                 MAC2STR(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
			//xTaskCreate(vTcpClient_Task, CLIENT_TASK_NAME, CLIENT_TASK_STACK_SIZE, NULL, CLIENT_TASK_PRIORITY, NULL);
			
		break;
		case SYSTEM_EVENT_AP_STADISCONNECTED:	//有sta从ESP32 Soft-Ap断开连接
			ESP_LOGI(TAG, "station:"MACSTR"leave, AID=%d",
                 MAC2STR(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
		break;
		
		default:
		break;
	}
	return ESP_OK;
}



void vWifi_Task(void * args)
{
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	//ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
	wifi_config_t sta_config = {
		.sta = {
			.ssid = "hompe-wifi",					//CONFIG_APSTA_STA_SSID,			
			.password = "Hompe@0321",				//CONFIG_APSTA_STA_PASSWORD,
			.bssid_set = false
		}
	};
	wifi_config_t ap_config = {
		.ap = {
			.ssid = "chzfmx_wifi",					//CONFIG_APSTA_AP_SSID,
			.password = "12345678",					//CONFIG_APSTA_AP_PASSWORD,
			.ssid_len = 0,
			.max_connection = 4,
			.authmode = WIFI_AUTH_WPA_PSK
		}
	};
	//ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &ap_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	esp_wifi_connect();
	for(;;)
	{
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
		
}




