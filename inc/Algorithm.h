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
#include "ConstVarible.h"

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
	uint8_t key;
	while (1)
	{
       key = rand() % 10;
	  if (0 != key)
	  {
		break;
	  }
	};
    return key;
}

void encryptData(Data* pData)
{
	uint8_t encipherKey = pData->encipherKey;
	for(int idx = 0; idx < MAXVALUE; ++idx)
	{
        if (pData->transmitData[idx] > encipherKey)
	    {
			printf("subtract idx = %d key = %d transmitData = %d",idx, encipherKey, pData->transmitData[idx]);
			pData->transmitData[idx] -= encipherKey;
			printf("transmitData1 = %d \n", pData->transmitData[idx]);
		}
		else
		{
			printf("plus idx = %d key = %d transmitData = %d",idx, encipherKey, pData->transmitData[idx]);
			pData->transmitData[idx] += encipherKey;
            pData->markFlag |= 1 << idx;
			printf("transmitData1 = %d markFlag=%d\n", pData->transmitData[idx], pData->markFlag);
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
	 uint8_t totolLength = 0;
	 uint8_t arrayLength = sizeof(pData->transmitData) / sizeof(pData->transmitData[0]);
	 uint8_t encipherNum = pData->encipherNum;
	 if (arrayLength % encipherNum)
	 {
		totolLength = (arrayLength/encipherNum + 1) * encipherNum;
	 }
	 else
	 {
		totolLength = arrayLength;
	 }
	 uint8_t *pExchangeData = (uint8_t *)malloc(totolLength * sizeof(pData->transmitData[0]));
	 if (NULL == pExchangeData)
	 {
        printf("malloc failed");
		return;
	 }
	 memset(pExchangeData, 0, sizeof(pData->transmitData[0]) * totolLength);
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