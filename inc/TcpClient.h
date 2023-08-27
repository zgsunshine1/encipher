#ifndef TCPSERVER_H
#define TCPSERVER_H
#define MAXLINE 4096
#define MAXVALUE 20
typedef struct decryptData 
{
   uint8_t encipherKey;
   uint8_t receiveData[MAXVALUE];
   uint32_t markFlag;
}decryptData;

decryptData receiveData;

int initClientSocket(int argc, char** argv, int* socketfd)
{
   struct sockaddr_in severaddr;	// ip address of server
	
	if (argc != 2) {
		printf("usage: ./client <ipadress>\n");
		return 0;
	}

	// socket init
	if ((*socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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

	if (connect(*socketfd, (struct sockaddr*)&severaddr, sizeof(severaddr)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		return 0;
	}
}
#endif