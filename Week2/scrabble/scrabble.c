/*
* File: example.c
* Author: name <yourmail@gmail.com>
* Copyright (c) 2024, name
* Public Domain.
* Version: 1.0
*
* Description:
* 拼字游戏，根据两位玩家输入的单词来计算得分，分高获胜
* check50 cs50/problems/2024/x/scrabble
* style50 scrabble.c
* submit50 cs50/problems/2024/x/scrabble
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string str_toupper(string s);
int score_word(string s);

int main(void)
{
    // 提示玩家输入单词
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // 将单词转化为得分，并比较分数
    int player1_score = score_word(str_toupper(player1));
    int player2_score = score_word(str_toupper(player2));

    // 判断获胜者
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!");
    }
    else if (player1_score < player2_score)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
	return 0;
}

// 根据单词统计得分
int score_word(string s)
{
    int score = 0;

    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        if (s[i] == 'A')
        {
            score += 1;
        }
        else if (s[i] == 'B')
        {
            score += 3;
        }
        else if (s[i] == 'C')
        {
            score += 3;
        }
        else if (s[i] == 'D')
        {
            score += 2;
        }
        else if (s[i] == 'E')
        {
            score += 1;
        }
        else if (s[i] == 'F')
        {
            score += 4;
        }
        else if (s[i] == 'G')
        {
            score += 2;
        }
        else if (s[i] == 'H')
        {
            score += 4;
        }
        else if (s[i] == 'I')
        {
            score += 1;
        }
        else if (s[i] == 'J')
        {
            score += 8;
        }
        else if (s[i] == 'K')
        {
            score += 5;
        }
        else if (s[i] == 'L')
        {
            score += 1;
        }
        else if (s[i] == 'M')
        {
            score += 3;
        }
        else if (s[i] == 'N')
        {
            score += 1;
        }
        else if (s[i] == 'O')
        {
            score += 1;
        }
        else if (s[i] == 'P')
        {
            score += 3;
        }
        else if (s[i] == 'Q')
        {
            score += 10;
        }
        else if (s[i] == 'R')
        {
            score += 1;
        }
        else if (s[i] == 'S')
        {
            score += 1;
        }
        else if (s[i] == 'T')
        {
            score += 1;
        }
        else if (s[i] == 'U')
        {
            score += 1;
        }
        else if (s[i] == 'V')
        {
            score += 4;
        }
        else if (s[i] == 'W')
        {
            score += 4;
        }
        else if (s[i] == 'X')
        {
            score += 8;
        }
        else if (s[i] == 'Y')
        {
            score += 4;
        }
        else if (s[i] == 'Z')
        {
            score += 10;
        }
        else
        {
            score += 0;
        }
    }

    return score;
}

// 将输入的字符串统一转变为大写
string str_toupper(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        s[i] = toupper(s[i]);
    }

    return s;
}
