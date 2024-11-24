/**
 * File: example.c
 * Author: name <yourmail@gmail.com>
 * Copyright (c) 2024, name
 * Public Domain.
 * Version: 1.0
 *
 * Description:
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates 最大候选人数量
#define MAX 9

// Candidates have name and vote count 定义候选人的数据结构为：名字，票数
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates 根据数据结构创建最大为9的数组
candidate candidates[MAX];

// Number of candidates 候选人数量
int candidate_count;

// Function prototypes 函数声明
bool vote(string name);
void print_winner();

int main(int argc, string argv[])
{
    // Check for invalid usage 检查命令行无效输入
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates 根据命令行参数个数得到候选人数量
    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters 获取要输入的票数
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote 检查输入的投票名和候选人名字是否一致
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;

}

// Print the winner (or winners) of the election
void print_winner()
{
	// 对candidates中的每个候选根据他们的票数进行排序
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - i - 1; j++)
        {
            if (candidates[j].votes < candidates[j + 1].votes)
            {
                candidate temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }

	// 根据排序输出最高票的候选，如果有多人票数相同一起输出（和排序第一的人对比，相等就输出）
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[0].votes)
        {
            printf("%s\n", candidates[i].name);
        }
		
		// 但凡碰到和最高票不同则直接退出，无须继续对比
		else
		{
			return;
		}
    }

}

