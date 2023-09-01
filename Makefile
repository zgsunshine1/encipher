CC = gcc
GPLUSPLUS = g++
CFLAGS = -g -Wall
GTEST = -Igtest/include -Lgtest/lib -lgtest -lgtest_main
SRC_DIRS = ./src/
INC_DIRS = ./inc/
TEST_DIRS = ./test/
DIR_BIN = ./bin/
OBJ_DIRS = ./obj/

all:server client operateFile
server:
	$(CC) $(CFLAGS) -o $(DIR_BIN)server $(SRC_DIRS)TcpServer.c -I $(INC_DIRS)
client:
	$(CC) $(CFLAGS) -o $(DIR_BIN)client $(SRC_DIRS)TcpClient.c -I $(INC_DIRS)
operateFile:
	$(CC) $(CFLAGS) -o $(DIR_BIN)operateFile $(SRC_DIRS)FileOperation.c $(SRC_DIRS)cJSON.c -I $(INC_DIRS)
TestAlgorithm:
	$(GPLUSPLUS) $(CFLAGS) $(TEST_DIRS)TestAlgorithm.c -o $(DIR_BIN)TestAlgorithm -I$(INC_DIRS) $(GTEST)

.PHONY:
clean:
	rm $(DIR_BIN)*

