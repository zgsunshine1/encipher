CC = gcc
GPLUSPLUS = g++
CFLAGS = -g -Wall
GTEST = -Igtest/include -Lgtest/lib -lgtest -lgtest_main
SRC_DIRS = ./src/
INC_DIRS = ./inc/
TEST_DIRS = ./test/
DIR_BIN = ./bin/
OBJ_DIRS = ./obj/

all:server client
server:TcpServer.o
	$(CC) $(CFLAGS) -o $(DIR_BIN)server TcpServer.o
TcpServer.o:$(SRC_DIRS)TcpServer.c
	$(CC) $(CFLAGS) -c $(SRC_DIRS)TcpServer.c -I $(INC_DIRS)
client:TcpClient.o
	$(CC) $(CFLAGS) -o $(DIR_BIN)client TcpClient.o
TcpClient.o:$(SRC_DIRS)TcpClient.c
	$(CC) $(CFLAGS) -c $(SRC_DIRS)TcpClient.c -I $(INC_DIRS)
TestAlgorithem:
	$(GPLUSPLUS) $(CFLAGS) $(TEST_DIRS)TestAlgorithem.c -o $(DIR_BIN)TestAlgorithem -I$(INC_DIRS) $(GTEST)
.PHONY:
clean:
	rm $(DIR_BIN)* *.o

