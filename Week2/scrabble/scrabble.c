/**
 * File: scrabble.c
    * Author: name <yourmail@gmail.com>
 * Copyright (c) 2024, name
 * Public Domain.
 * Version: 1.1
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

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

string str_toupper(string s);
int score_word(string s);

int main(void)
{
    // 提示玩家输入单词
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int player1_score = score_word(player1);
    int player2_score = score_word(player2);

    // 判断获胜者
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1_score < player2_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

// 根据单词统计得分
int score_word(string s)
{
    int score = 0;

    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        char word = toupper(s[i]);

        if (word > 64 && word < 91)
        {
            score += POINTS[word - 'A'];
        }
    }

    return score;
}

