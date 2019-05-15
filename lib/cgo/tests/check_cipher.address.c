#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SKYCOIN_ADDRESS_VALID "2GgFvqoyk9RjwVzj8tqfcXVXB4orBwoc9qv"

// TestSuite(cipher_address, .init = setup, .fini = teardown);

extern unsigned char buff[1024];

START_TEST(TestDecodeBase58Address)
{
    GoString strAddr = {SKYCOIN_ADDRESS_VALID, 35};
    cipher__Address addr;
    GoUint32 err = SKY_cipher_DecodeBase58Address(strAddr, &addr);
    ck_assert_int_eq(err, SKY_OK);

    char tempStr[50];
    int errorcode;

    // preceding whitespace is invalid
    strcpy(tempStr, " ");
    strcat(tempStr, SKYCOIN_ADDRESS_VALID);
    strAddr.p = tempStr;
    strAddr.n = strlen(tempStr);
    errorcode = SKY_cipher_DecodeBase58Address(strAddr, &addr);
    ck_assert_msg(errorcode == SKY_ERROR, "preceding whitespace is invalid");

    // preceding zeroes are invalid
    strcpy(tempStr, "000");
    strcat(tempStr, SKYCOIN_ADDRESS_VALID);
    strAddr.p = tempStr;
    strAddr.n = strlen(tempStr);
    errorcode = SKY_cipher_DecodeBase58Address(strAddr, &addr);
    ck_assert_msg(errorcode == SKY_ERROR, "leading zeroes prefix are invalid");

    // trailing whitespace is invalid
    strcpy(tempStr, SKYCOIN_ADDRESS_VALID);
    strcat(tempStr, " ");
    strAddr.p = tempStr;
    strAddr.n = strlen(tempStr);
    errorcode = SKY_cipher_DecodeBase58Address(strAddr, &addr);
    ck_assert_msg(errorcode == SKY_ERROR, "trailing whitespace is invalid");

    // trailing zeroes are invalid
    strcpy(tempStr, SKYCOIN_ADDRESS_VALID);
    strcat(tempStr, "000");
    strAddr.p = tempStr;
    strAddr.n = strlen(tempStr);
    errorcode = SKY_cipher_DecodeBase58Address(strAddr, &addr);
    ck_assert_msg(errorcode == SKY_ERROR, "trailing zeroes suffix are invalid");

    cipher__PubKey p;
    cipher__SecKey s;
    errorcode = SKY_cipher_GenerateKeyPair(&p, &s);
    ck_assert(errorcode == SKY_OK);
    cipher__Address a;
    errorcode = SKY_cipher_AddressFromPubKey(&p, &a);
    ck_assert(errorcode == SKY_OK);
    GoSlice b;
    coin__UxArray Cub;
    Cub.data = buff;
    Cub.len = 0;
    Cub.cap = sizeof(buff);
    errorcode = SKY_cipher_Address_Bytes(&addr, &Cub);
    ck_assert_msg(errorcode == SKY_OK, "Fail SKY_cipher_Address_Bytes");
    b.cap = Cub.cap;
    b.data = Cub.data;
    b.len = Cub.len;

    int len_b = b.len;
    char bufferHead[1024];
    GoString_ h = {bufferHead, 0};
    b.len = (GoInt)(len_b / 2);
    errorcode = SKY_base58_Hex2Base58(b, &h);
    ck_assert(errorcode == SKY_OK);
    char bufferHeadTmp[1024];
    GoString tmph = {bufferHeadTmp, 0};
    tmph.n = h.n;
    tmph.p = h.p;
    errorcode = SKY_cipher_DecodeBase58Address(tmph, &addr);
    ck_assert_msg(errorcode == SKY_ErrAddressInvalidLength, "Fail %X", errorcode);
    b.len = len_b;
    errorcode = SKY_base58_Hex2Base58(b, &h);
    ck_assert(errorcode == SKY_OK);
    tmph.n = h.n;
    tmph.p = h.p;
    errorcode = SKY_cipher_DecodeBase58Address(tmph, &addr);
    ck_assert_msg(errorcode == SKY_OK, "Fail %X", errorcode);
}
END_TEST

// define test suite and cases
Suite* cipher_address(void)
{
    Suite* s = suite_create("Load cipher.address");
    TCase* tc;

    tc = tcase_create("cipher.address");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestDecodeBase58Address);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}