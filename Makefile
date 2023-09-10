CC = gcc
GPLUSPLUS = g++
CFLAGS = -g -Wall
GTEST = -Igtest/include -Lgtest/lib -lgtest -lgtest_main
CMOCKATEST = -lcmocka
SRC_DIRS = ./src/
INC_DIRS = ./inc/
TEST_DIRS = ./test/
DIR_BIN = ./bin/
OBJ_DIRS = ./obj/
CURL_DIRS =  ../curl/install_Curl/include
CURL_LIBDIRS =  ../curl/install_Curl/lib
CURL_LIB = -lcurl
all:server client operateFile
server:
	$(CC) $(CFLAGS) -o $(DIR_BIN)server $(SRC_DIRS)TcpServer.c -I $(INC_DIRS)
client:
	$(CC) $(CFLAGS) -o $(DIR_BIN)client $(SRC_DIRS)TcpClient.c -I $(INC_DIRS)
operateFile:
	$(CC) $(CFLAGS) -o $(DIR_BIN)operateFile $(SRC_DIRS)FileOperation.c $(SRC_DIRS)cJSON.c -I $(INC_DIRS)
useCurl:
	$(CC) $(CFLAGS) -o $(DIR_BIN)useCurl $(SRC_DIRS)Curl.c -I $(CURL_DIRS) -I $(INC_DIRS)  -L $(CURL_LIBDIRS) $(CURL_LIB)
TestAlgorithm:
	$(GPLUSPLUS) $(CFLAGS) $(TEST_DIRS)TestAlgorithm.c -o $(DIR_BIN)TestAlgorithm -I$(INC_DIRS) $(GTEST)
TestAlgorithm_sample:
	$(CC) $(CFLAGS) $(TEST_DIRS)TestAlgorithm_simple.c -o $(DIR_BIN)TestAlgorithm_sample -I$(INC_DIRS) $(CMOCKATEST)
.PHONY:
clean:
	rm $(DIR_BIN)*

