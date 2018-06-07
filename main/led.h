#ifndef __LED_H
#define __LED_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "sdkconfig.h"


#define LED_TASK_NAME 				"vLed_Task"
#define LED_TASK_STACK_SIZE			2048
#define LED_TASK_PRIORITY			10

extern void led_init();
extern void vLed_Task(void * args);


#endif

