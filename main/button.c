#include "button.h"

#define KEY1				GPIO_NUM_34
#define KEY2				GPIO_NUM_35

static xQueueHandle key_evt_queue = NULL;
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
	uint32_t gpio_num = (uint32_t)arg;
	xQueueSendFromISR(key_evt_queue, &gpio_num, NULL);
}

void button_init()
{
	gpio_config_t io_con = {
		.intr_type = GPIO_PIN_INTR_POSEDGE,			//上升沿中断
		.mode = GPIO_MODE_INPUT,
		.pin_bit_mask = (1ULL << KEY1) | (1ULL << KEY2),
		.pull_up_en = 1,
		.pull_down_en = 0,
	};
	gpio_config(&io_con);

	//定义消息队列
	key_evt_queue = xQueueCreate(10, sizeof(uint32_t));
	//注册中断函数
	gpio_install_isr_service(0);
	gpio_isr_handler_add(KEY1, gpio_isr_handler, (void *)KEY1);
	//gpio_set_intr_type(KEY2, GPIO_PIN_INTR_ANYEDGE);
	gpio_isr_handler_add(KEY2, gpio_isr_handler, (void *)KEY2);
}



void vButton_Task(void *args)
{
	uint32_t io_num;
	button_init();
	for(;;)
	{
		if(xQueueReceive(key_evt_queue, &io_num, portMAX_DELAY))
		{
			printf("GPIO[%d] intr, val:%d\n", io_num, gpio_get_level(io_num));
		}
	}
}








