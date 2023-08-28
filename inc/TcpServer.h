#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "Algorithm.h"

int initServerSocket(int* listenfd, struct sockaddr_in* severaddr)
{
	if ((*listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("create sever socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	
	memset(severaddr, 0, sizeof(struct sockaddr_in));
	severaddr->sin_family = AF_INET;
	severaddr->sin_addr.s_addr = htonl(INADDR_ANY);
	severaddr->sin_port = htons(6666);
	
	if (bind(*listenfd, (struct sockaddr *)severaddr, sizeof(*severaddr)) == -1) {
		printf("bind sever socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	
	if (listen(*listenfd, 10) == -1) {
		printf("listen sever socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}

    printf("=====Waiting for client's request===\n");
	return 1;
}
bool mappingEncipherReq(const int connfd, Data* pData)
{
	EncipherMethod encipher;
	recv(connfd, (void *)&encipher, sizeof(EncipherMethod), 0);
	printf("recieve method %s\n",encipher.method);
	if(strcmp(encipher.method, request))
	{
		printf("recieve encipherNum %hhu\n",encipher.encipherNum);
		pData->encipherNum = encipher.encipherNum;
		return true;
	}
	return false;	
}
#endif