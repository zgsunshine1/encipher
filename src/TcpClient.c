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
	int socketfd;
	char recvline[MAXLINE], sendline[MAXLINE];
	
    initClientSocket(argc, argv, &socketfd);

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
	return 1;
}
