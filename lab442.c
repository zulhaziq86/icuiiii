#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char*message;
	int optval;
	socklen_t optien = sizeof(optval);

	//create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}

	/* Check the status for the keepalive option */
	if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optien) <0) {
	perror("getsockopt()");
	close(socket_desc);
	exit(EXIT_FAILURE);
	}	
	printf("SO_KEEPALIVE is %s\n", (optval ? "ON": "OFF"));

	/*  Set the option alive*/
	optval = 1;
	optien = sizeof(optval);
	if(setsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, optien) < 0) {
	perror("setsockopt()");
	close(socket_desc);
	}
	return 0;
}
