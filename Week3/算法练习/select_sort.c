/*
* File: select_sort.c
* Author: name <yourmail@gmail.com>
* Copyright (c) 2024, name
* Public Domain.
* Version: 1.0
*
* Description: 用选择排序算法对数组进行排序
*
*/

#include <cs50.h>
#include <stdio.h>

void select_sort(int list[], int n);

int main(void)
{
    int list[10] = {2, 1, 5, 8, 3, 7, 4, 6, 9, 10};
    select_sort(list, 10);
}

// 选择排序
void select_sort(int list[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;

        for (int j = i + 1; j < n; j++)
        {

            if (list[j] < list[min_idx])
            {
                min_idx = j;
            }
        }

        if (min_idx != i)
        {
            int _ = list[i];
            list[i] = list[min_idx];
            list[min_idx] = _;
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
