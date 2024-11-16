#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // 输入一个数字，如果不是正数则不断提问
    int n;
    do
    {
        n = get_int("Please in put a number: ");
    }
    while (n < 1);

    // 根据输入的数字打印金字塔，注意：前面的空格为n-i
    for (int i = 1; i < n + 1; i++)
    {

        for (int k = 0; k < n - i; k++)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
