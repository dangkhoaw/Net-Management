/*
Usage:
    string encoded = Base64("string to encode").encode();
    string decoded = Base64("string to decode").decode();
*/
#include "base64.h"

Base64::Base64(const string str) : str(str) {}

string Base64::encode()
{
    int len = this->str.length();
    string base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string result;
    int i = 0;
    while (i < len)
    {
        result += base64Table[(str[i] & 0b11111100) >> 2];
        result += base64Table[((str[i] & 0b00000011) << 4) | ((i + 1 < len ? str[i + 1] & 0b11110000 : 0) >> 4)];
        result += i + 1 < len ? base64Table[((str[i + 1] & 0b00001111) << 2) | ((i + 2 < len ? str[i + 2] & 0b11000000 : 0) >> 6)] : '=';
        result += i + 2 < len ? base64Table[str[i + 2] & 0b00111111] : '=';
        i += 3;
    }
    return result;
}

string Base64::decode()
{
    int len = this->str.length();
    string base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string result;
    int i = 0;
    while (i < len)
    {
        result += (base64Table.find(str[i]) << 2) | ((i + 1 < len ? base64Table.find(str[i + 1]) : 0) >> 4);
        if (str[i + 2] != '=')
            result += ((base64Table.find(str[i + 1]))) << 4 | ((i + 2 < len ? base64Table.find(str[i + 2]) : 0) >> 2);
        if (str[i + 3] != '=')
            result += (base64Table.find(str[i + 2]) << 6) | (i + 3 < len ? base64Table.find(str[i + 3]) : 0);
        i += 4;
    }
    return result;
}

Base64::~Base64() {}