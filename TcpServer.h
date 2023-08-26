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
#define MAXVALUE 20
typedef unsigned char  uint8_t;  
typedef unsigned short uint16_t;
//typedef unsigned long  uint32_t;  
uint8_t inputData[MAXVALUE] = {
0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01,
0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D};

typedef struct encipherData 
{
   uint8_t encipherKey;
   uint8_t sendData[MAXVALUE];
   uint32_t markFlag;
}encipherData;

encipherData sendCipherData;

const uint8_t getCryptKey()
{
	srand(time(NULL));
    uint8_t key = rand() % 10;
    printf("value=%d\n",key);
    return key;
}

void encryptData(encipherData& sendCipherData)
{
	uint8_t encipherKey = getCryptKey();
	uint8_t *pCipherData = inputData;
	sendCipherData.encipherKey = encipherKey;
	uint32_t &markFlag = sendCipherData.markFlag;
	for(int idx = 0; idx < MAXVALUE; ++idx)
	{
        if (pCipherData[idx] > encipherKey)
	    {
			sendCipherData.sendData[idx] = pCipherData[idx] - encipherKey;
			printf("origin idx = %d value1 = %d key = %d sendData = %d \n",idx, pCipherData[idx], encipherKey, sendCipherData.sendData[idx]);
		}
		else
		{
			sendCipherData.sendData[idx] = pCipherData[idx] + encipherKey;
            markFlag |= 1 << idx;
			printf("origin idx = %d value2 = %d key = %d sendData = %d \n",idx, pCipherData[idx], encipherKey, sendCipherData.sendData[idx]);
		}
	}
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