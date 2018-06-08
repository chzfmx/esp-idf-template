#ifndef __TCP_CLIENT_H
#define __TCP_CLIENT_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "lwip/sockets.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_log.h"


#define CLIENT_TASK_NAME 				"vTcpClent_Task"
#define CLIENT_TASK_STACK_SIZE			2048
#define CLIENT_TASK_PRIORITY			10

extern void vTcpClient_Task(void * arg);

#endif





