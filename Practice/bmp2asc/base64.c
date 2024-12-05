#include <stdio.h>
#include <stdlib.h>

const char *encode_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

char* base64_encode(char *datas, int datas_length, int *encoded_str_length){
    // 计算最终base64字符串的长度
    *encoded_str_length = (datas_length + 2) / 3 * 4;

    // 申请内存空间
    char *encoded_str = (char*)malloc(*encoded_str_length + 1);
    char *encoded_ptr = encoded_str;

    // 首先，3个字符一组，进行编码
    for(int i = 0, n = datas_length/3; i < n; ++i){
        encoded_ptr[0] = encode_table[(datas[0] >> 2) & 0x3F];
        encoded_ptr[1] = encode_table[((datas[0] << 4) & 0x30) | ((datas[1] >> 4) & 0x0F)];
        encoded_ptr[2] = encode_table[((datas[1] << 2) & 0x3C) | ((datas[2] >> 6) & 0x03)];
        encoded_ptr[3] = encode_table[datas[2] & 0x3F];
        encoded_ptr += 4;
        datas += 3;
    }

    // 当字符串长度不是3的倍数时，对剩下的字符进行编码
    int n = datas_length % 3;
    if(n == 1){
        encoded_ptr[0] = encode_table[(datas[0] >> 2) & 0x3F];
        encoded_ptr[1] = encode_table[(datas[0] << 4) & 0x30];
        encoded_ptr[2] = encode_table[64];
        encoded_ptr[3] = encode_table[64];
        encoded_ptr += 4;
    }
    else if(n == 2){
        encoded_ptr[0] = encode_table[(datas[0] >> 2) & 0x3F];
        encoded_ptr[1] = encode_table[((datas[0] << 4) & 0x30) | ((datas[1] >> 4) & 0x0F)];
        encoded_ptr[2] = encode_table[(datas[1] << 2) & 0x3C];
        encoded_ptr[3] = encode_table[64];
        encoded_ptr += 4;
    }

    *encoded_ptr = '\0';
    return encoded_str;
}
