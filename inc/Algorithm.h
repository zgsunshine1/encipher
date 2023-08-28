#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdbool.h>
#include <time.h>
#define MAXLINE 10
#define MAXVALUE 20
const char request[] = "encipher";
uint8_t inputData[MAXVALUE] = {
0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01,
0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D};

typedef struct EncipherMethod
{
	char method[MAXLINE];
	uint8_t encipherNum;
}EncipherMethod;

typedef struct Data 
{
   uint8_t encipherKey;
   uint8_t encipherNum;
   uint8_t transmitData[MAXVALUE];
   uint32_t markFlag;
}Data;

const uint8_t getCryptKey()
{
	srand(time(NULL));
    uint8_t key = rand() % 10;
    printf("value=%d\n",key);
    return key;
}

void encryptData(Data* pData, uint8_t *recData)
{
	uint8_t encipherKey = getCryptKey();
	uint8_t *pCipherData = recData;
	pData->encipherKey = encipherKey;
	for(int idx = 0; idx < MAXVALUE; ++idx)
	{
        if (pCipherData[idx] > encipherKey)
	    {
			pData->transmitData[idx] = pCipherData[idx] - encipherKey;
			printf("subtract idx = %d value1 = %d key = %d transmitData = %d \n",idx, pCipherData[idx], encipherKey, pData->transmitData[idx]);
		}
		else
		{
			pData->transmitData[idx] = pCipherData[idx] + encipherKey;
            pData->markFlag |= 1 << idx;
			printf("plus idx = %d value2 = %d key = %d transmitData = %d \n",idx, pCipherData[idx], encipherKey, pData->transmitData[idx]);
		}
	}
}

void exchangeEncryptData(Data* pData)
{
   uint8_t encipherNum = pData->encipherNum;
   if (encipherNum <= 1)
   {
	 return;
   }
   else
   {
	 uint8_t *pExchangeData = NULL;
	 uint8_t totolLength = 0;
	 uint8_t arrayLength = sizeof(pData->transmitData) / sizeof(pData->transmitData[0]);
	 uint8_t encipherNum = pData->encipherNum;
	 if (arrayLength % encipherNum)
	 {
		totolLength = (arrayLength/encipherNum + 1) * encipherNum;
	    pExchangeData = malloc( totolLength * sizeof(pData->transmitData[0]));
	 }
	 else
	 {
		totolLength = arrayLength;
		pExchangeData = malloc(arrayLength * sizeof(pData->transmitData[0]));
	 }
	 for (int i = 0; i < totolLength; )
	 {
		for (int j = 0; j < encipherNum; j++)
		{
			pExchangeData[i + j] = pData->transmitData[i+ encipherNum -1 - j];
			printf("exchangeEncryptData idx = %d transmitData = %d \n",i + j, pExchangeData[i + j]);
		}
		i+= encipherNum;
	 }
	 for (int i = 0; i < totolLength; i++)
	 {
	   pData->transmitData[i] = pExchangeData[i];
	 }
 
     free(pExchangeData);
	 pExchangeData = NULL;
   }
   return;
}

void decryptData(Data* pData)
{
    int size = sizeof(pData->transmitData);
	uint32_t markFlag = pData->markFlag;
	printf("encipherKey %d, size %ld makeFlag =%d\n", pData->encipherKey, sizeof(pData->transmitData), pData->markFlag);
	
	for(int idx = 0; idx < size; ++idx)
	{
	   if (markFlag & (1 << idx))
	   {
          pData->transmitData[idx] -= pData->encipherKey;
	   }
	   else
	   {
		 pData->transmitData[idx] += pData->encipherKey;
	   }
	   printf("original Data %d idx %d\n", pData->transmitData[idx], idx);
	}
}

#endif