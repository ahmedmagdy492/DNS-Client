#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 53
#define LOG 0
#define BUFFER_SIZE 4096

#include "logger.h"
#include "packet_resolver.h"
#include "dns_client.h"


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <url>\n", argv[0]);
		return -1;
	}

	char *packet = NULL;
	int len = 0;
	prepare_packet(&packet, argv[1], &len);

	char* ip = "8.8.8.8";
	init(ip, PORT);
	log_msg("socket created");

	// preparing the server address and sending data
	log_msg("sending udp request to 8.8.8.8 ...");
	send_data(packet, len);
	
	// receiving data
	log_msg("request has been sent successfully");
	char buffer[BUFFER_SIZE];
	recv_data(buffer, BUFFER_SIZE);
	printf("%s\n", buffer);

	// clean up
	free(packet);
	clean_up();
}
