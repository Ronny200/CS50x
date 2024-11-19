/**
 * File: credit.c
 * Author: Ronny.H <yq.worm@gmail.com>
 * Copyright (c) 2024, Ronny.H
 * Public Domain.
 * Version: 1.0
 *
 * Description:
 * 检查给定信用卡号的有效性，如果有效则给出对应所属公司.
 * 测试卡号:
 * VISA:4003600000000014, 4012888888881881
 * AMEX:378282246310005, 371449635398431
 * Mastercard:5555555555554444, 5105105105105100
 * check50 cs50/problems/2024/x/credit
 * style50 credit.c
 * submit50 cs50/problems/2024/x/credit
 */

#include <cs50.h>
#include <stdio.h>

int get_len(long long int num);
int is_card(long long int num);
int get_comp_code(long long int num);

int main(void)
{
	long long int card_number;
	
	do
	{
		card_number = get_long_long("Please in put your card number: ");
	}
	while (card_number <= 0);
	
	int card_len = get_len(card_number);
	
	// 计算数字长度，如果长度符合则校验判断是否属于信用卡，如果不是则INVALID
	if ((card_len == 13 || card_len == 15 || card_len == 16) && is_card(card_number) != 0)
	{
		int card = get_comp_code(card_number);
		
		if ((card == 34 || card == 37) && card_len == 15)
		{
			// American Express美国运通卡15位数字以 34 或 37 开头
			printf("AMEX\n");
		}
		else if ((card == 51 || card == 52 || card == 53 || card == 54 || card == 55) &&
			card_len == 16)
		{
			// MasterCard万事达卡16位数字 51、52、53、54  55 开头
			printf("MASTERCARD\n");
		}
		else if (card >= 40 && card <= 49 && (card_len == 13 || card_len == 16))
		{
			// Visa卡13和16位数字4开头
			printf("VISA\n");
		}
		else
		{
			printf("INVALID\n");
		}
	}
	else
	{
		printf("INVALID\n");
	}
}

// 获取卡号头两位数用来获取来源公司
int get_comp_code(long long int num)
{
	while (num > 99)
	{
		num /= 10;
	}
	
	return num;
}

// 校验卡号是否正确
int is_card(long long int num)
{
	int sum = 0;
	int count = 1;
	
	while (num > 0)
	{
		int digit = num % 10;
		num /= 10;
		
		if (count % 2 == 0)
		{
			if (digit * 2 > 9)
			{
				sum += digit * 2 - 9;
			}
			else
			{
				sum += digit * 2;
			}
		}
		else
		{
			sum += digit;
		}
		
		count++;
	}
	
	return sum % 10 == 0;
}

// 获取输入数字的长度并返回长度
int get_len(long long int num)
{
	int len = 0;
	
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	
	return len;
}

