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
#include <string.h>
#define MAXLINE 4096

unsigned char inputData[20] = {
0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01,
0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D};

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

    printf("=====Waiting for client's request===\n");
	return 1;
}
#endif