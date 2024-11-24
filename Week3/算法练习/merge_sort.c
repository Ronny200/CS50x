/*
* File: merge_sort.c
* Author: name <yourmail@gmail.com>
* Copyright (c) 2024, name
* Public Domain.
* Version: 1.0
*
* Description: 用归并排序算法对数组进行排序
*
*/

#include <stdio.h>
#include <stdlib.h>

void merge_sort(int list[], int l, int r);
void merge(int list[], int left, int right, int mid);
void print_list(int list[], int n);

int main(void)
{
    int list[10] = {2, 1, 5, 8, 3, 7, 4, 6, 9, 10};
	merge_sort(list, 0, 9);
	print_list(list, 10);
}

// 归并排序
void merge_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
		merge(list, left, right, mid);
    }
}

// 合并数组
void merge(int list[], int left, int right, int mid)
{
    // 临时存储左右两边数组
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = list[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = list[mid + 1 + j];

    // 合并两个数组
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            list[k] = L[i];
            i++;
            k++;
        }
        else
        {
            list[k] = R[j];
            j++;
            k++;
        }
    }

    //判断哪个数组有多余未添加的数（剩下的为有序无需对比直接添加）

    while (i < n1)
    {
        list[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        list[k] = R[j];
        j++;
        k++;
    }
}


// 打印数组
void print_list(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", list[i]);
    }

    printf("\n");

    return;
}

