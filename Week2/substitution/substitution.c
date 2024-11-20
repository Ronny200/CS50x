/**
 * File: substitution.c
 * Author: name <yourmail@gmail.com>
 * Copyright (c) 2024, name
 * Public Domain.
 * Version: 1.0
 *
 * Description:
 * 通过密钥进行加密，密钥无视大小写但加密后必须和明文对应
 *
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// KEY = "YTNSHKVEFXRBAUQZCLWDMIPGJO";
int argv_is_key(string key);
string encrype_text(string s, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key", argv[0]);
        return 1;
    }
    else if (strlen(argv[1]) != 26 || argv_is_key(argv[1]) == 1)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext:  ");
        printf("ciphertext: %s", encrype_text(plaintext, argv[1]));
        printf("\n");
    }
}

// 对明文进行加密
string encrype_text(string s, string key)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = tolower(key[s[i] - 97]);
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = toupper(key[s[i] - 65]);
        }
        else
        {
            s[i] = s[i];
        }
    }

    return s;
}

// 检查key是否是纯字母以及是否重复
int argv_is_key(string key)
{
    int letter_array[26] = {0};

    for (int i = 0; i < 26; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return 1;
        }

        int letter = toupper(key[i]) - 65;

        if (letter_array[letter] != 0)
        {
            return 1;
        }
        else
        {
            letter_array[letter] = 1;
        }
    }

    return 0;
}
