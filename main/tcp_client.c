#include "tcp_client.h"

#define TAG					"[vTcpClient_Task]"
#define PORT				50000
#define SERVER_ADDR			"192.168.4.2"

char msg[] = "hello ,you are connected!";


void vTcpClient_Task(void * arg)
{
	struct sockaddr_in server_addr;
	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		ESP_LOGE(TAG, "failed to create sock_fd!\n");
			
	}
	ESP_LOGI(TAG, "wait 3 s!\n");
	vTaskDelay(3000 / portTICK_PERIOD_MS);
	//raw_memset()
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	server_addr.sin_port = htons(PORT);
	connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	ESP_LOGI(TAG, "connect!\n");
	while(1)
	{
		vTaskDelay(3000 / portTICK_PERIOD_MS);
		send(sock_fd, (char *)msg, sizeof(msg), 0);
		
	}
}





