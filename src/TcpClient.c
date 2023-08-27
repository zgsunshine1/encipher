#include"TcpClient.h"

int main(int argc, char** argv) {
	int socketfd;
	char sendline[MAXLINE];
	
    initClientSocket(argc, argv, &socketfd);

	printf("send message to sever: \n");
	fgets(sendline, MAXLINE, stdin);
	
	if (send(socketfd, sendline, strlen(sendline), 0) < 0) {
		printf("send message error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
	Data receiveDecryptData;
	recv(socketfd, (void *)&receiveDecryptData, sizeof(Data), 0);
    decryptData(&receiveDecryptData);

	close(socketfd);
	return 1;
}
