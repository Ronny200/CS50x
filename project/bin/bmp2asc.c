#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint16_t WORD;

typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__)) BITMAPFILEHEADER;

typedef struct
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} __attribute__((__packed__)) BITMAPINFOHEADER;

typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__)) RGBTRIPLE;

// ASCII字符集，从最浅到最深
static const char ascii_chars_simple[] = "@%#*+=-:. ";
static const char ascii_chars_complex[] =
    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

const char *ascii_chars = ascii_chars_simple;
size_t NUM_CHARS = sizeof(ascii_chars_simple) - 1;

void parse_args(int argc, char *argv[], char **infile, char **outfile, char **mode, int *num_cols);
char get_ascii_char(int gray);

int main(int argc, char *argv[])
{
    // 默认设置
    char *infile = "..\\convert\\bmp\\output_2251.bmp";
    char *outfile = "..\\convert\\asc\\output_2251.txt";
    char *mode = "simple";
    int num_cols = 150;

    // 解析命令行参数
    parse_args(argc, argv, &infile, &outfile, &mode, &num_cols);

    if (strcmp(mode, "complex") == 0)
    {
        ascii_chars = ascii_chars_complex;
        NUM_CHARS = sizeof(ascii_chars_complex) - 1;
    }
    else
    {
        ascii_chars = ascii_chars_simple;
        NUM_CHARS = sizeof(ascii_chars_simple) - 1;
    }

    FILE *inptr = fopen(infile, "rb");
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

    // 获取图像尺寸
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // 计算每个字符代表的像素区域大小
    double cell_width = width / num_cols;
    double cell_height = 2 * cell_width;
    int num_rows = (int) (height / cell_height);

    // 如果列数或行数太多，调整默认设置
    if (num_cols > width || num_rows > height)
    {
        printf("Too many columns or rows. Use default setting\n");
        cell_width = 6;
        cell_height = 12;
        num_cols = (int) (width / cell_width);
        num_rows = (int) (height / cell_height);
    }

    // 为图像分配内存（二维数组）
    RGBTRIPLE(*image)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));
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

    // 将位图转成灰度图并转换为ASCII字符
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            int avg_gray = 0;
            int pixel_count = 0;

            // 计算每个cell的平均灰度值
            for (int y = i * cell_height; y < (i + 1) * cell_height && y < height; y++)
            {
                for (int x = j * cell_width; x < (j + 1) * cell_width && x < width; x++)
                {
                    int gray = round(0.299 * image[y][x].rgbtRed + 0.587 * image[y][x].rgbtGreen +
                                     0.114 * image[y][x].rgbtBlue);
                    avg_gray += gray;
                    pixel_count++;
                }
            }

            if (pixel_count > 0)
            {
                avg_gray /= pixel_count;
            }

            // 根据灰度值选择字符
            fputc(get_ascii_char(avg_gray), outptr);
        }
        fputc('\n', outptr); // 每一行结束后换行
    }

    // 释放内存
    free(image);
    fclose(inptr);
    fclose(outptr);
    return 0;
}

// 解析命令行参数
void parse_args(int argc, char *argv[], char **infile, char **outfile, char **mode, int *num_cols)
{
    int opt;
    while ((opt = getopt(argc, argv, "i:o:m:n:")) != -1)
    {
        switch (opt)
        {
            case 'i':
                *infile = optarg;
                break;
            case 'o':
                *outfile = optarg;
                break;
            case 'm':
                *mode = optarg;
                break;
            case 'n':
                *num_cols = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -i infile.bmp -o outfile.txt [-m mode] [-n num_cols]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

// 获取对应的ASCII字符
char get_ascii_char(int gray)
{
    int index = (gray * (NUM_CHARS - 1)) / 255;
    return ascii_chars[index];
}
