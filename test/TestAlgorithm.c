#include <gtest/gtest.h>
#include "Algorithm.h"
TEST(Algorithm__Test, GiveEncipherMethodAndData_WhenEnciperSuccess_ThenCheckResult)
{
    /*这里设置输入条件，随机秘钥值为7,输入一组数据，验证经过加密后的数据值*/
    Data cipherData;
    cipherData.encipherKey = 7;
    cipherData.encipherNum = 1;
    encryptData(&cipherData, inputData);
    uint8_t expectData[MAXVALUE] = {
    92, 117, 112, 116, 235, 100, 104, 190, 41, 8,
    96, 36, 247, 208, 164, 111, 195, 123, 194, 118, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
    for (int i = 0; i < MAXVALUE; ++i)
    {
       EXPECT_EQ(expectData[i], cipherData.transmitData[i]);
    }
}

TEST(Algorithm__Test, GiveEncipherMethodAndData_WhenDecryptSuccess_ThenCheckResult)
{
    /*这里设置输入条件，随机秘钥值为3,输入一组数据，加密操作和解密操作之后验证最后结果等于输入数据*/
    Data cipherData;
    cipherData.encipherKey = 3;
    cipherData.markFlag = 0;
    encryptData(&cipherData, inputData);
    decryptData(&cipherData);
    for (int i = 0; i < MAXVALUE; ++i)
    {
       EXPECT_EQ(inputData[i], cipherData.transmitData[i]);
    }
}

TEST(Algorithm__Test, GiveEncipherMethodAndData_WhenExchageEncipherSuccess_ThenCheckResult)
{
    /*这里设置输入条件，随机秘钥值为5,输入一组数据，加密操作之后再按照7个为一组进行逆序操作验证最后结果*/
    Data cipherData;
    cipherData.encipherKey = 5;
    cipherData.markFlag = 0;
    cipherData.encipherNum = 6;
    memset(cipherData.transmitData, 0, sizeof(cipherData.transmitData));
    encryptData(&cipherData, inputData);
    exchangeEncryptData(&cipherData);
    uint8_t expectData[MAXVALUE] = {
    102, 237, 118, 114, 119, 94, 
    38, 98, 6, 43, 192, 106,
    125, 197, 113, 166, 210, 249,
    5, 5, 5, 5, 120, 196, 
    5, 5, 5, 5, 5, 5};
    for (int i = 0; i < MAXVALUE; ++i)
    {
       EXPECT_EQ(expectData[i], cipherData.transmitData[i]);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
    return 0;
}
