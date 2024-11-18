/*
* File: cash.c
* Author: Ronny.H <yq.worm@gmail.com>
* Copyright (c) 2024, Ronny.H
* Public Domain.
* Version: 1.0
*
* Description:
* 根据给的金额计算找零，按照零钱大小来给顾客零钱，能25的就25，不到25的就10，依次类推，最后给出总共多少个硬币.
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //定义找零总数
    int number = 0;
    int money;

    //提示用户输入大于0的零钱
    do
    {
        money = get_int("Change owed: ");
    }
    while (money < 1);

    //是否可以使用25
    while (money >= 25)
    {
        money -= 25;
        number += 1;
    }

    //是否可以使用10
    while (money >= 10)
    {
        money -= 10;
        number += 1;
    }

    //是否可以使用5
    while (money >= 5)
    {
        money -= 5;
        number += 1;
    }

    //是否可以使用1
    while (money >= 1)
    {
        money -= 1;
        number += 1;
    }

    //输出找零总数
    printf("%i", number);

}
