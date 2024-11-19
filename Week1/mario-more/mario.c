/**
 * File: mario.c
 * Author: Ronny.H <yq.worm@gmail.com>
 * Copyright (c) 2024, Ronny.H
 * Public Domain.
 * Version: 1.0
 *
 * Description:
 * 输入一个数字建立左右两边对等的#字塔
 * check50 cs50/problems/2024/x/mario/more
 * style50 mario.c
 * submit50 cs50/problems/2024/x/mario/more
 */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        // 用户输入高度，如果不是1~8的整数则不断循环要求重新输入
        height = get_int("Please in put height number: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        // 左侧前空格，每行空格相当于总行数减去当前行数，因为i从0开始，所以要-1
        for (int n = height - i - 1; n > 0; n--)
        {
            printf(" ");
        }

        for (int m = 0; m <= i; m++)
        {
            printf("#");
        }

        // 插入两排#中间的空格
        printf("  ");

        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}

