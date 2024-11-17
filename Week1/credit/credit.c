/*
* File: example.h
* Author: Ronny.H <yq.worm@gmail.com>
* Copyright (c) 2024, Ronny.H
* Public Domain.
* Version: 1.0
*
* Description:
* 检查给定信用卡号的有效性.
*/

#include <cs50.c>
#include <stdio.h>

int get_length(long long int num);
int is_card(long long int num);
int company(long long int num);

int main(void)
{
	long long int number = 0;	//获取信用卡数字

	do
	{
		number = get_long_long("Please in put the number: ");
	}
	while (number < 0);		//只能输入大于0的数字

	int length = get_length(number);

	//判断是否是信用卡信用卡
	if ((length == 15 || length == 13 || length == 16) && is_card(number) == 1)
	{
		//是信用卡
		int card = company(number);		//获取卡号开头用来判断公司归属

		if ((card == 34 || card == 37) && length == 15)
		{
			//American Express美国运通卡15位数字以 34 或 37 开头
			printf("AMES\n");
		}
		else if ((card == 51 || card == 52 || card == 53 || card == 54 || card == 55) && length == 16)
		{
			//MasterCard万事达卡16位数字 51、52、53、54  55 开头
			printf("MASTERCARD\n");
		}
		else if (card >= 40 && card <= 49 && (length == 13 || length == 16))
		{
			//Visa卡13和16位数字4开头
			printf("VISA\n");
		}
		else
		{
			//是信用卡但是不知道公司归属
			printf("I don't know!");
		}
	}
	else
	{
		//不是信用卡
		printf("INVALID\n");

	}
}

int company(long long int num)
{
	//获取卡号的开头两位数字
	while (num > 99)
	{
		num /= 10;
	}

	return num;
}

int is_card(long long int num)
{
	//利用算法判断信用卡校验和是否正确，是返回1，否返回0
	int sum = 0;
	int conut = 1;
	int dig = 0;

	while (num != 0)
	{
		dig = num % 10;

		if (conut % 2 == 0)
		{
			if (dig * 2 > 9)
			{
				sum = sum + (dig * 2 - 9);
			}
			else
			{
				sum += dig * 2;
			}
		}
		else
		{
			sum += dig;
		}

		num /= 10;

		conut++;
	}

	if (sum % 10 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int get_length(long long int num)
{
	//获取用户输入数字的长度
	int lenght = 0;

	while (num > 0)
	{
		num /= 10;
		lenght += 1;
	}

	//printf("%i\n", lenght);
	return lenght;
}
