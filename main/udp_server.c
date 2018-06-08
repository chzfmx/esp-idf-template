#include "udp_server.h"


#define TAG					"[vUdpServer_Task]"
#define PORT				50000
#define SERVER_ADDR			"192.168.4.2"




void vUdpServer_Task(void * arg)
{
	struct sockaddr_in server_addr;
	int sock_fd;					//server socket
	int err;
	int count = 0;
	int opt = -1;
	char msg[] = "the message broadcast!";
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd == -1)
	{
		ESP_LOGE(TAG, "failed to create sock_fd");
		
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_BROADCAST;			//广播
	//server_addr.sin_addr.s_addr = INADDR_ANY; 		//广播

	//server_addr.sin_addr.s_addr = inet_addr("192.168.4.2");
	server_addr.sin_port = htons(PORT);
	/*
	err = setsockopt(sock_fd,SOL_SOCKET,SO_BROADCAST,(char *)&opt,sizeof(opt));
	if (err == -1)
	{
		ESP_LOGE(TAG, "failed to setsocketopt");
	}
	*/
	/*
	err = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (err == -1)
	{
		ESP_LOGE(TAG, "failed to bind sock_fd");
	}
	*/
	while(1)
	{
		vTaskDelay(3000 / portTICK_PERIOD_MS);
		count = sendto(sock_fd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
		if (count < 0)
		{
			ESP_LOGI(TAG, "send err!");
		}
		else
		{
			ESP_LOGI(TAG, "send ok!");
		}
		
	}
		
}



