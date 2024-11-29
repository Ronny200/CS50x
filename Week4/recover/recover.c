#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
int const BLOCK_SIZE = 512;
int is_jpeg(BYTE byte);

int main(int argc, char *argv[])
{
	// 判断是否有多余参数
	if (argc != 2)
	{
		printf("Usage: ./recover FILE\n");
		return 1;
	}
	
	// 判断是否能打开指定文件
	FILE *file = fopen(argv[1], "rb");
	if (file == NULL)
	{
		printf("Can't open the file\n");
		fclose(file);
		return 1;
	}
	
	// 定义读取块
	FILE *output = NULL;
	BYTE buff[BLOCK_SIZE];
	int count = 0;
	
	while (fread(buff, BLOCK_SIZE, 1, file))
	{
		if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && !is_jpeg(buff[3]))
		{
			if (count)
			{
				fclose(output);
			}
			
			// 按照编号写入文件名
			char *filename = malloc(8 * sizeof(char));
			sprintf(filename, "%03d.jpg", count);
			output = fopen(filename, "w");
			free(filename);
			count++;
		}
		
		if (count)
		{
			fwrite(buff, BLOCK_SIZE, 1, output);
		}
	}
	
	fclose(file);
	fclose(output);
}

// 判断第四个字节是否是jpeg规定中的一个
int is_jpeg(BYTE num)
{
	BYTE array[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
		0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};
	for (int i = 0; i < sizeof(array); i++)
	{
		if (num == array[i])
		{
			return 0;
		}
	}
	return 1;
}

