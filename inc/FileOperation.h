#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConstVarible.h"
#include "cJSON.h"
void writeBinaryFile()
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
void readBinaryFile()
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
void writeFile(const cJSON* root)
{
	FILE *fp = fopen("create.json","w");
	char *buf = cJSON_Print(root);
	fwrite(buf,strlen(buf),1,fp);
	fclose(fp);
}

void writeJsonFile()
{
  cJSON* root = cJSON_CreateObject();
	cJSON* item = cJSON_CreateObject();
	cJSON* next = cJSON_CreateObject();
	cJSON* obj = cJSON_CreateObject();

	//在root节点下添加
	cJSON_AddItemToObject(root,"listBook",cJSON_CreateNumber(3));
	cJSON_AddItemToObject(root,"book",cJSON_CreateString("human"));
	cJSON_AddItemToObject(root,"author",cJSON_CreateString("angle"));

	//添加数组
	cJSON* array = NULL;
	cJSON_AddItemToObject(root,"books",array=cJSON_CreateArray());

	//添加数组对象
	cJSON_AddItemToArray(array,obj);
	cJSON_AddItemToObject(obj,"name",cJSON_CreateString("math"));
  cJSON_AddStringToObject(obj,"type","123");

	cJSON_AddItemToArray(array,obj=cJSON_CreateObject());
	cJSON_AddItemToObject(obj,"name",cJSON_CreateString("english"));
	cJSON_AddStringToObject(obj,"type","456");

	cJSON_AddItemToObject(root, "sem", item);//root节点下添加sem节点
	cJSON_AddItemToObject(item, "slots", next);//se节点下添加item节点
	cJSON_AddItemToObject(next, "name", cJSON_CreateString("lingyang"));//添加name节点

	printf("%s\n", cJSON_Print(root));
  writeFile(root);
	cJSON_Delete(root);
  root = NULL;
}

#endif