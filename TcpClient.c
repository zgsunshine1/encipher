#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"TcpClient.h"

int main(int argc, char** argv) {
	int socketfd, n;
	char recvline[MAXLINE], sendline[MAXLINE];
	
	struct sockaddr_in severaddr;	// ip address of server
	
	if (argc != 2) {
		printf("usage: ./client <ipadress>\n");
		return 0;
	}

	// socket init
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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

	if (connect(socketfd, (struct sockaddr*)&severaddr, sizeof(severaddr)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}

	printf("send message to sever: \n");
	fgets(sendline, MAXLINE, stdin);
	
	if (send(socketfd, sendline, strlen(sendline), 0) < 0) {
		printf("send message error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	decryptData receiveDecryptData;
	int length = recv(socketfd, (void *)&receiveDecryptData, sizeof(decryptData), 0);
	int size = sizeof(receiveDecryptData.receiveData);
	uint32_t markFlag = receiveDecryptData.markFlag;
	printf("encipherKey %d, size %ld makeFlag =%d\n", receiveDecryptData.encipherKey, sizeof(receiveDecryptData.receiveData), receiveDecryptData.markFlag);
	
	for(int idx = 0; idx < size; ++idx)
	{
	   if (markFlag & (1 << idx))
	   {
          receiveDecryptData.receiveData[idx] -= receiveDecryptData.encipherKey;
	   }
	   else
	   {
		 receiveDecryptData.receiveData[idx] += receiveDecryptData.encipherKey;
	   }
	   printf("receiveData %d idx %d length %d\n", receiveDecryptData.receiveData[idx], idx, length);
	}

	close(socketfd);
	return 0;
}
