#include "TcpServer.h"

int main(int argc, char** argv) {
	int listenfd, connfd;	// socket id of sever and client
	struct sockaddr_in severaddr;	// ip address of server
	
    initServerSocket(&listenfd, &severaddr);
	Data sendCipherData;
	while(1) {
		if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1) {
			printf("accept sever socket error: %s(errno: %d)\n", strerror(errno), errno);
			return 0;
		}
        if (mappingEncipherReq(connfd, &sendCipherData))
		{
		   sendCipherData.encipherKey = getCryptKey();
		   printf("generate key for clinet: %d\n", sendCipherData.encipherKey);
		   encryptData(&sendCipherData, inputData);
		   exchangeEncryptData(&sendCipherData);
		   send(connfd, (const void*)&sendCipherData, sizeof(sendCipherData), 0);
		}
	}
	close(connfd);
	close(listenfd);
	return 0;
	}
