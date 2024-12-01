#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// 定义长参数结构
static struct option long_options[] = {
    {"binary", required_argument, NULL, 'i'},  {"blur", required_argument, NULL, 'b'},
    {"edges", required_argument, NULL, 'e'},   {"grayscale", required_argument, NULL, 'g'},
    {"reflect", required_argument, NULL, 'r'}, {0, 0, 0, 0}};

char *create_out_filename(char *input);

void write_outfile(int height, int width, int padding, FILE *outptr, RGBTRIPLE image[height][width],
                   BITMAPFILEHEADER bf, BITMAPINFOHEADER bi);

// 主程序入口
int main(int argc, char *argv[])
{
    // 解析参数
    int options_index = 0;
    char *options = "i:b:e:g:r:";
    int arg = getopt_long(argc, argv, options, long_options, &options_index);

    // 判断是否是无效参数
    if (arg == '?')
    {
        printf("Unknown option '%c'.\n", optopt);
        return 1;
    }

    // 判断是否只有一个参数
    if (getopt_long(argc, argv, options, long_options, &options_index) != -1)
    {
        printf("Only one option.\n");
        return 2;
    }

    // 判断选项后的参数是否刚好是1位，上面已经执行过两轮getopt，所以optind为3
    if (argc != optind)
    {
        printf("Usage: %s [flag] infile\n", argv[0]);
        return 3;
    }

    // 定义文件名
    char *infile = argv[optind - 1];
    char *outfile = create_out_filename(infile);

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open the %s.\n", infile);
        return 4;
    }

    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // 读取位图头文件
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // 读取位图头部信息部分
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // 确认读取的文件是24-bit无压缩bmp4.0格式文件
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 ||
        bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // 读取info头部信息获取图像的尺寸大小
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // 为图像分配内存（二维数组）
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // 检测一行上的填充像素
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // 遍历输入图片，将有效内容存入image，跳过填充的内容
    for (int i = 0; i < height; i++)
    {
        // 读取一行中的有效位图像素
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // 将指针偏移padding个字节跳过填充的内容
        fseek(inptr, padding, SEEK_CUR);
    }

    // 根据命令行参数开始执行 i:b:e:g:r:
    switch (arg)
    {
        case 'b':
            blur(height, width, image);
            write_outfile(height, width, padding, outptr, image, bf, bi);
            break;

        case 'e':
            edges(height, width, image);
            write_outfile(height, width, padding, outptr, image, bf, bi);
            break;

        case 'g':
            grayscale(height, width, image);
            write_outfile(height, width, padding, outptr, image, bf, bi);
            break;

        case 'r':
            reflect(height, width, image);
            write_outfile(height, width, padding, outptr, image, bf, bi);
            break;

        case 'i':
            printf("convert ascii\n");
            // blur(height, width, image);
            // write_outfile(height, width, padding, outptr, image, bf, bi);
            break;

        default:
            printf("Unknown option.\n");
            return 1;
    }

    free(outfile);
    free(image);
    fclose(inptr);
    fclose(outptr);
    return 0;
}

// 将处理完的图像写入文件
void write_outfile(int height, int width, int padding, FILE *outptr, RGBTRIPLE image[height][width],
                   BITMAPFILEHEADER bf, BITMAPINFOHEADER bi)
{
    fwrite(&bf, sizeof(bf), 1, outptr);
    fwrite(&bi, sizeof(bi), 1, outptr);

    // 将处理过的像素写入文件
    for (int i = 0; i < height; i++)
    {
        // 将一行数据写入文件
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // 每行不足4的倍数就填充
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    return;
}

// 根据文件名自定义输出的文件名
char *create_out_filename(char *input)
{
    int len = strlen(input);
    char *name = malloc(len + 5);
    char *dot = strrchr(input, '.');

    strncpy(name, input, dot - input);
    name[dot - input] = '\0';
    strcat(name, "_out");
    strcat(name, dot);
    return name;
}
