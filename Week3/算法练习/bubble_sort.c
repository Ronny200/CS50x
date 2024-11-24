/*
* File: bubble_sort.c
* Author: name <yourmail@gmail.com>
* Copyright (c) 2024, name
* Public Domain.
* Version: 1.0
*
* Description: 用冒泡排序算法对数组进行排序
*
*/

#include <cs50.h>
#include <stdio.h>

void bubble_sort(int list[], int n);

int main(void)
{
    int list[10] = {2, 1, 5, 8, 3, 7, 4, 6, 9, 10};
    bubble_sort(list, 10);
}

// 冒泡排序
void bubble_sort(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (list[j] > list[j + 1])
            {
                int _ = list[j];
                list[j] = list[j + 1];
                list[j + 1] = _;
            }
        }
    }
	
	// 打印数组
    for (int i = 0; i < n; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\n");

    return;
}

