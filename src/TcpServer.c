#include "TcpServer.h"

int main(int argc, char** argv) {
	int listenfd, connfd;	// socket id of sever and client
	struct sockaddr_in severaddr;	// ip address of server
	
	char buf[MAXLINE];
    initServerSocket(&listenfd, &severaddr);
	const char request[] = "encipher";
	while(1) {
		if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1) {
			printf("accept sever socket error: %s(errno: %d)\n", strerror(errno), errno);
			return 0;
		}
		int length;
		length = recv(connfd, buf, MAXLINE, 0);
		buf[length] = '\n';
		if(strcmp(buf, request))
		{
		   printf("generate key for clinet: %d\n", getCryptKey());
		   Data sendCipherData;
		   encryptData(&sendCipherData);
		   send(connfd, (const void*)&sendCipherData, sizeof(sendCipherData), 0);
		}
	}
	close(connfd);
	close(listenfd);
	return 0;
	}
