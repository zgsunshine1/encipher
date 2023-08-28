#include"TcpClient.h"

int main(int argc, char** argv) {
	int socketfd;
    if (initClientSocket(argc, argv, &socketfd))
	{
      sendRequest(socketfd);
	  Data receiveDecryptData;
	  recv(socketfd, (void *)&receiveDecryptData, sizeof(Data), 0);
      decryptData(&receiveDecryptData);
	}
	close(socketfd);
	return 1;
}
