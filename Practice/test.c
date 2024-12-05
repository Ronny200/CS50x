#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

const char * version = "1.0.0";
int run_program(const char *path);
int file_exists(const char *path);

int main(int argc, char *argv[])
{
    // 判断选项和参数
    int option;
    while ((option = getopt(argc, argv, "hvr:s:")) != -1)
    {
        switch (option)
        {
            case 'h':
                printf("help option selected.\n");
                break;
            case 'v':
                printf("%s: %s.\n", argv[0], version);
                break;
            case 'r':
                run_program(optarg);
                break;
            case '?':
                printf("Unknown options.\n");
                break;
            default:
                printf("This is default options.\n");
                break;
        }
    }

    if (optind == 1 && argc == 1)
    {
        if (!file_exists("run.bat"))
        {
            run_program("run.bat");
        }
    }
    return 0;
}

// 判断默认文件是否存在
int file_exists(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file)
    {
        fclose(file);
        return 0;
    }
    return 1;
}

// 进程调用外部程序并退出自身
int run_program(const char *path)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    size_t len = sizeof(path);
    char dest[len + 1];
    strncpy(dest, path, len);
    dest[len] = '\0';

    // 启动新的进程
    if (CreateProcess(
            NULL,
            dest,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)
        ) {
        ExitProcess(0); // 立即退出当前进程
    }
    else
    {
        printf("CreateProcess failed.\n");
        return 1;
    }
    return 0;
}
