/**
 * File: readability.c
 * Author: name <yourmail@gmail.com>
 * Copyright (c) 2024, name
 * Public Domain.
 * Version: 1.0
 *
 * Description:
 * 根据一段文本统计里面的字母，单词，句子的数量来输出属于哪个阅读等级
 *
 * check50 cs50/problems/2024/x/readability
 * style50 readability.c
 * submit50 cs50/problems/2024/x/readability
 */

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_index(string text);

int main(void)
{
    string text = get_string("Text: ");
    int index = get_index(text);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    return 0;
}

// 统计字母，单词，句子的数量并返回Coleman-Liau 指数
int get_index(string text)
{
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        else if (isblank(text[i]))
        {
            words += 1;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }

    words += 1;
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    return round(0.0588 * L - 0.296 * S - 15.8);
}
