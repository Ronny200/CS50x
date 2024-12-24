#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

// conver to ascii
void bmp_binary(int height, int width, RGBTRIPLE image[height][width]);
void write_ascii_to_file(FILE *file, int height, int width, RGBTRIPLE image[height][width]);

// 主程序入口
int main(int argc, char *argv[])
{
  // 解析参数
  if (argc != 3)
  {
    printf("Usage: %s infile.bmp outfile.txt\n", argv[0]);
    return 1;
  }

  // 定义文件名
  char *infile = argv[1];
  char *outfile = argv[2];

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
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
      bi.biBitCount != 24 || bi.biCompression != 0)
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

  // 二值图转换
  bmp_binary(height, width, image);

  // 字符转换
  write_ascii_to_file(outptr, height, width, image);

  // 释放内存
  free(image);
  fclose(inptr);
  fclose(outptr);
  return 0;
}

// 将位图根据灰度输出成字符
void bmp_binary(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      int gray = round(
          (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) /
          3.0);
      gray = gray > 195 ? 255 : 0;
      image[i][j].rgbtRed = gray;
      image[i][j].rgbtGreen = gray;
      image[i][j].rgbtBlue = gray;
    }
  }
  return;
}

// 将二值图转成字符
void write_ascii_to_file(FILE *file, int height, int width, RGBTRIPLE image[height][width])
{
  // 定义字符映射
  const char black_char = '@';
  const char white_char = ' ';

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // 根据灰度值选择字符
      if (image[i][j].rgbtRed == 255)
      {
        fputc(white_char, file); // 白色像素用空格表示
      }
      else
      {
        fputc(black_char, file); // 黑色像素用 # 表示
      }
    }
    fputc('\n', file); // 每一行结束后换行
  }

  fclose(file);
}