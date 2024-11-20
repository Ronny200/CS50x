/**
 * File: caesar.c
 * Author: name <yourmail@gmail.com>
 * Copyright (c) 2024, name
 * Public Domain.
 * Version: 1.0
 *
 * Description:
 * 对输入的字符串进行加密，使用参数作为密钥，参数必须为10进制整数
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int argv_is_int(string num);
string encrype_text(string s, int n);

int main(int argc, string argv[])
{
	if (argc != 2 || atoi(argv[1]) == 0 || argv_is_int(argv[1]))
	{
		printf("Usage: %s key\n", argv[0]);
		return 1;
	}
	else
	{
		string plaintext = get_string("plaintext:  ");
		printf("ciphertext: %s", encrype_text(plaintext, atoi(argv[1])));
		printf("\n");
		return 0;
	}
}

// 对字符串加密并返回密文
string encrype_text(string s, int key)
{
	for (int i = 0, n = strlen(s); i < n; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] = (s[i] - 65 + key) % 26 + 65;
		}
		else if (s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] = (s[i] - 97 + key) % 26 + 97;
		}
		else
		{
			s[i] = s[i];
		}
	}
	
	return s;
}

// 判断参数是否为十进制
int argv_is_int(string num)
{
	for (int i = 0, n = strlen(num); i < n; i++)
	{
		if (isdigit(num[i]) == 0)
		{
			return 1;
		}
	}
	
	return 0;
}

