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
		/*算法匹配和秘钥生成并发送给客户*/
        if (mappingEncipherReq(connfd, &sendCipherData))
		{
		   sendCipherData.encipherKey = getCryptKey();
		   printf("generate key for clinet: %d\n", sendCipherData.encipherKey);
		   send(connfd, (const void*)&sendCipherData, sizeof(sendCipherData), 0);
		}
		/*客户端收到秘钥之后发送的要加密的数据，服务器端收到该数据之后进行加密*/
        recieveClientData(connfd, &sendCipherData);
	}
	close(connfd);
	close(listenfd);
	return 0;
	}
