#ifndef __WIFI_NET_H
#define __WIFI_NET_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "sdkconfig.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define WIFI_TASK_NAME 				"vWifi_Task"
#define WIFI_TASK_STACK_SIZE		4096
#define WIFI_TASK_PRIORITY			8


extern void vWifi_Task(void * args);


#endif

