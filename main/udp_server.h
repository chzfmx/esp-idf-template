#ifndef __UDP_SERVER_H
#define __UDP_SERVER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "lwip/sockets.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_log.h"


#define UDPSERVER_TASK_NAME 				"vUdpServer_Task"
#define UDPSERVER_TASK_STACK_SIZE			2048
#define UDPSERVER_TASK_PRIORITY				10

extern void vUdpServer_Task(void * arg);

#endif

