/*
* File: hello.c
* Author: Ronny.H <yq.worm@gmail.com>
* Copyright (c) 2024, Ronny.H
* Public Domain.
* Version: 1.0
*
* Description:
* 输入你的名字然后输出
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
