#ifndef CONSTVARIBLE_H
#define CONSTVARIBLE_H
#include <stdint.h>
#define MAXLINE 10
#define MAXVALUE 30
const char request[] = "encipher";
uint8_t inputData[MAXVALUE] = {
0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01,
0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D};
#endif