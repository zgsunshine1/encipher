#include "TcpServer.h"

int main(int argc, char** argv) {
	int listenfd, connfd;	// socket id of sever and client
	struct sockaddr_in severaddr;	// ip address of server
	
	char buf[MAXLINE];
	int n;
	
    initServerSocket(&listenfd, &severaddr);
	const char request[] = "encipher";
	while(1) {
		if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1) {
			printf("accept sever socket error: %s(errno: %d)\n", strerror(errno), errno);
			return 0;
		}
		
		n = recv(connfd, buf, MAXLINE, 0);
		buf[n] = '\n';
		if(strcmp(buf, request))
		{
		   printf("generate key for clinet: %d\n", getCryptKey());
		   encryptData(&sendCipherData);
		   int size = send(connfd, (const void*)&sendCipherData, sizeof(sendCipherData), 0);
		}
	}
	close(connfd);
	close(listenfd);
	return 0;
	}
