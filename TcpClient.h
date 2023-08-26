
#define MAXLINE 4096
#define MAXVALUE 20
typedef struct decryptData 
{
   uint8_t encipherKey;
   uint8_t receiveData[MAXVALUE];
   uint32_t markFlag;
}decryptData;

decryptData receiveData;