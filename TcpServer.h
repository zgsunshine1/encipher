#ifndef TCPSERVER_H
#define TCPSERVER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include <time.h>
#define MAXLINE 4096

const unsigned char getCryptKey()
{
	srand(time(NULL));
    unsigned char key = rand() % 10;
    printf("value=%d\n",key);
    return key;
}

int initServerSocket(int& listenfd, struct sockaddr_in& severaddr)
{
	// socket init
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("create sever socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	
	memset(&severaddr, 0, sizeof(severaddr));
	severaddr.sin_family = AF_INET;
	severaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	severaddr.sin_port = htons(6666);
	
	// bind socket id
	if (bind(listenfd, (struct sockaddr*)&severaddr, sizeof(severaddr)) == -1) {
		printf("bind sever socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	
	// linsten socket id
	if (listen(listenfd, 10) == -1) {
		printf("listen sever socket error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	return 1;
}
#endif