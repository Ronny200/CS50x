#include <cs50.c>
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

    //是否可以使用10

    //是否可以使用5

    //是否可以使用1

    //输出找零总数

}
