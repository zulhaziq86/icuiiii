#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
//Driver function
int main(int argc, char *argv[]) 
{
	int socket_desc, new_socket, t;
	struct sockaddr_in server, client;
	char *message, buffer[100];

	//socket create nad verification
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("Socket creation failed. . \n");
	}	

	//assign IP, PORT
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//binding newly created socket to given ip and verfication
	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) 
	{
		puts("socket bind failed...\n");
		exit(1);
	}
	//Now server is ready to listen and verfication

	t = listen(socket_desc, 3);
	
	if(t == -1)
	{
		printf("Error in listening");
		exit(1);
	}

	
	socklen_t length = sizeof(client);

	new_socket = (accept(socket_desc,(struct sockaddr*)&client, &length));
	if(new_socket == -1)
	{
		printf("Error in temporary socket creatioin");
		exit(1);
	}
	
	while(1)
	{
		t = recv(new_socket, buffer, 100, 0);

		if(t == -1)
		{
			printf("Error in receiving");
			exit(1);
		}
			printf("Client: %s ", buffer);	//message from client
			printf("\nServer: "); // message for client	
			fgets(buffer,100,stdin);	
			if(strncmp(buffer,"bye",3)==0)
			break;
			t=send(new_socket, buffer, 100, 0);
			if(t==-1)
			{
				printf("Error in sending");
				exit(1);
			}
	}		

	close(new_socket);

	exit(0);

	return 0;


}

