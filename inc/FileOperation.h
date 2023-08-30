#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConstVarible.h"
void writeFile()
{
   FILE *fp = NULL;
   fp = fopen("./test.txt", "wb+");
   fwrite(inputData,sizeof(char),sizeof(inputData),fp);
   fclose(fp);
   for(int i = 0; i < MAXVALUE; i++)
   {
     printf("inputValue:%hhd\n", inputData[i]);
   }
}
void readFile()
{
   FILE *fp = NULL;
   fp = fopen("./test.txt", "rb+");
   uint8_t outPutData[MAXVALUE];
   fread(outPutData,sizeof(char),sizeof(outPutData),fp);
   fclose(fp);
   for(int i = 0; i < MAXVALUE; i++)
   {
     printf("outputValue:%hhd\n", outPutData[i]);
   }
}
#endif