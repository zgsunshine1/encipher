#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "Algorithm.h"

Data receiveData;

int initClientSocket(int argc, char** argv, int* socketfd)
{
    struct sockaddr_in severaddr;

	if (argc != 2) {
		printf("usage: ./client <ipadress>\n");
		return 0;
	}
	if ((*socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create client socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	
	memset(&severaddr, 0, sizeof(severaddr));
	severaddr.sin_family = AF_INET;
	severaddr.sin_port = htons(6666);
	
	if (inet_pton(AF_INET, argv[1], &severaddr.sin_addr) < 0) {
		printf("inet_pton error for: %s\n", argv[1]);
		return 0;
	}

	if (connect(*socketfd, (struct sockaddr*)&severaddr, sizeof(severaddr)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	return 1;
}

void sendRequest(const int socketfd)
{
	EncipherMethod encipher;
    while(1)
	{
        printf("please input encipher method: \n");
	    fgets(encipher.method, MAXLINE, stdin);
		if(strcmp(encipher.method, request))
		{
			break;
		}
	};

	while (1)
	{
		printf("please input encipher number: %d\n", encipher.encipherNum);
		scanf("%hhu", &encipher.encipherNum);
		if( 0 < encipher.encipherNum && encipher.encipherNum < 10)
		{
			break;			
		}
	};
	if (send(socketfd, (const void*)&encipher, sizeof(EncipherMethod), 0) < 0) 
	{
		printf("send message error: %s(errno: %d)\n", strerror(errno), errno);
	}
}
#endif