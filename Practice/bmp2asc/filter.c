#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// 定义长参数结构
static struct option long_options[] = 
{
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {"binary", required_argument, NULL, 'i'},
    {"blur", required_argument, NULL, 'b'},
    {"edges", required_argument, NULL, 'e'},
    {"grayscale", required_argument, NULL, 'g'},
    {"reflect", required_argument, NULL, 'r'},
    {0, 0, 0, 0}
};

// 主程序入口
int main(int argc, char *argv[])
{
    int options_index = 0;
    int arg = 0;
    while ((arg = getopt_long(argc, argv, "hvi:b:e:g:r:", long_options, &options_index)) != -1)
    {
        
    }
}