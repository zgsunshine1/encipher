#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include "../inc/Algorithm.h"
#include "cmocka.h"

static void GiveEncipherMethodAndData_WhenEnciperSuccess_ThenCheckResult() {
        /*这里设置输入条件，随机秘钥值为7,输入一组数据，验证经过加密后的数据值*/
    Data cipherData;
    cipherData.encipherKey = 7;
    cipherData.encipherNum = 1;
    memcpy(cipherData.transmitData, inputData, sizeof(inputData));
    encryptData(&cipherData);
    uint8_t expectData[MAXVALUE] = {
    92, 117, 112, 116, 235, 100, 104, 190, 41, 8,
    96, 36, 247, 208, 164, 111, 195, 123, 194, 118, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
    for (int i = 0; i < MAXVALUE; ++i)
    {
       assert_int_equal(expectData[i], cipherData.transmitData[i]);
    }
}

static void GiveEncipherMethodAndData_WhenDecryptSuccess_ThenCheckResult() {
    /*这里设置输入条件，随机秘钥值为3,输入一组数据，加密操作和解密操作之后验证最后结果等于输入数据*/
    Data cipherData;
    cipherData.encipherKey = 3;
    cipherData.markFlag = 0;
    memcpy(cipherData.transmitData, inputData, sizeof(inputData));
    encryptData(&cipherData);
    decryptData(&cipherData);
    for (int i = 0; i < MAXVALUE; ++i)
    {
       assert_int_equal(inputData[i], cipherData.transmitData[i]);
    }
}

static void GiveEncipherMethodAndData_WhenExchageEncipherSuccess_ThenCheckResult() {
    /*这里设置输入条件，随机秘钥值为5,输入一组数据，加密操作之后再按照7个为一组进行逆序操作验证最后结果*/
    Data cipherData;
    cipherData.encipherKey = 5;
    cipherData.markFlag = 0;
    cipherData.encipherNum = 6;
    memset(cipherData.transmitData, 0, sizeof(cipherData.transmitData));
    memcpy(cipherData.transmitData, inputData, sizeof(inputData));
    encryptData(&cipherData);
    exchangeEncryptData(&cipherData);
    uint8_t expectData[MAXVALUE] = {
    102, 237, 118, 114, 119, 94, 
    38, 98, 6, 43, 192, 106,
    125, 197, 113, 166, 210, 249,
    5, 5, 5, 5, 120, 196, 
    5, 5, 5, 5, 5, 5};
    for (int i = 0; i < MAXVALUE; ++i)
    {
       assert_int_equal(expectData[i], cipherData.transmitData[i]);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(GiveEncipherMethodAndData_WhenEnciperSuccess_ThenCheckResult),
        cmocka_unit_test(GiveEncipherMethodAndData_WhenDecryptSuccess_ThenCheckResult),
        cmocka_unit_test(GiveEncipherMethodAndData_WhenExchageEncipherSuccess_ThenCheckResult),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
