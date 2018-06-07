#ifndef __BUTTON_H
#define __BUTTON_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BUTTON_TASK_NAME 				"vButton_Task"
#define BUTTON_TASK_STACK_SIZE			2048
#define BUTTON_TASK_PRIORITY			9

extern void vButton_Task(void *args);


#endif



