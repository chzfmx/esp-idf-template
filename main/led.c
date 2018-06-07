#include "led.h"


#define LED0 GPIO_NUM_5

void led_init()
{
	gpio_config_t io_conf = {
		.intr_type = GPIO_PIN_INTR_DISABLE,
		.mode = GPIO_MODE_OUTPUT,
		.pin_bit_mask = (1ULL << LED0),
		.pull_up_en = 0,
		.pull_down_en = 0,
	};
	gpio_config(&io_conf);
	
}

void vLed_Task(void* args)
{
	int level = 0;
	led_init();
	for(;;)
	{
		level ? (level = 0) : (level = 1);
		gpio_set_level(LED0, level);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		//printf("led_task: running......\r\n");
	}		
}




