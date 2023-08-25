CC = gcc
CFLAGS = -g -Wall
CLIBS = -lpthread -lssl -ldl -lcurses
GTEST = -Igtest/include -Lgtest/lib -lgtest -lgtest_main
all:server client
server:TcpServer.o
	g++ -g -o server TcpServer.o
TcpServer.o:TcpServer.c
	g++ -g -c TcpServer.c
client:TcpClient.o
	g++ -g -o client TcpClient.o
TcpClient.o:TcpClient.c
	g++ -g -c TcpClient.c
clean:
	rm server client *.o 

