#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	int port = 8888;
	char creply[2000];

	//create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc < 0)
	{
		printf("Could not create socket\n");
	}
	else
		printf("socket created\n");	
	
	//prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.0.161");
	server.sin_port = htons(port);
	
	//bind 
	if( bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
                printf("bind failed port: %d\n", port);
        }
	else
 	      	printf("bind done port: %d \n", port);

	//listen 
	if (listen(socket_desc, 3) < 0)
	{
		printf("Cannot listen to port %d \n", port);
	}
	else
		printf("Listening to port %d \n", port);

	c = sizeof(struct sockaddr_in);
	while ((new_socket = accept(socket_desc, (struct sockaddr *)&server, (socklen_t*)&c)) )
	{	
		printf("Request incoming...\n");
		printf("Request message: ");
		
		recv(new_socket, creply, 2000, 0 );	
		puts(creply);
	}
	
	close(socket_desc);
	return 0;	

}
	
