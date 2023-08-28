#include"TcpClient.h"

int main(int argc, char** argv) {
	int socketfd;
    if (initClientSocket(argc, argv, &socketfd))
	{
      sendRequest(socketfd);
	  Data data;
	  recv(socketfd, (void *)&data, sizeof(Data), 0);
	  printf("encipherKey %d", data.encipherKey);
	  memcpy(data.transmitData, inputData, sizeof(inputData));

	  sendData(socketfd, &data);
	  recv(socketfd, (void *)&data, sizeof(Data), 0);
	  exchangeEncryptData(&data);
      decryptData(&data);
	}
	close(socketfd);
	return 1;
}
