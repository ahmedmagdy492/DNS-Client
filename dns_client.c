#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "dns_client.h"

static char* IP = NULL;
static int PORT = 0;
static int udp_socket;

void init(char* ip, int port)
{
    IP = ip;
    PORT = port;
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (udp_socket == -1)
	{
		perror("Error while creating socket");
		exit(-1);
	}
}

void send_data(char* packet, int len)
{
    struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_aton(IP, &server_addr.sin_addr);

    int send_result = sendto(udp_socket, packet, sizeof(int) * len, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

	if (send_result == -1)
	{
		perror("Error while sending message to host");
		exit(-1);
	}
}

void recv_data(char *buffer, int len)
{
    struct sockaddr_in client_addr = {0};
	socklen_t client_len;

	int recv_data = recvfrom(udp_socket, buffer, sizeof(char) * len, MSG_WAITALL, (struct sockaddr *)&client_addr, &client_len);
	if (recv_data == -1)
	{
		perror("Error while receving data from the server");
		exit(-1);
	}
}

void clean_up()
{
	close(udp_socket);
}