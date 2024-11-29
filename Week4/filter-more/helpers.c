#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int gray =
			round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
			image[i][j].rgbtRed = gray;
			image[i][j].rgbtGreen = gray;
			image[i][j].rgbtBlue = gray;
		}
	}
	return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE temp;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			temp = image[i][j];
			image[i][j] = image[i][width - j - 1];
			image[i][width - j - 1] = temp;
		}
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE temp[height][width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			temp[i][j] = image[i][j];
		}
	}
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int sum_red = 0;
			int sum_green = 0;
			int sum_blue = 0;
			int count = 0;
			
			for (int di = -1; di <= 1; di++)
			{
				for (int dj = -1; dj <= 1; dj++)
				{
					int fi = i + di;
					int fj = j + dj;
					if (fi >= 0 && fi < height && fj >= 0 && fj < width)
					{
						sum_red += temp[fi][fj].rgbtRed;
						sum_green += temp[fi][fj].rgbtGreen;
						sum_blue += temp[fi][fj].rgbtBlue;
						count++;
					}
				}
			}
			
			image[i][j].rgbtRed = round((float) sum_red / count);
			image[i][j].rgbtGreen = round((float) sum_green / count);
			image[i][j].rgbtBlue = round((float) sum_blue / count);
		}
	}
	return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE temp[height][width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			temp[i][j] = image[i][j];
		}
	}
	
	int gx_array[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int gy_array[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int gx_red = 0;
			int gx_green = 0;
			int gx_blue = 0;
			int gy_red = 0;
			int gy_green = 0;
			int gy_blue = 0;
			
			for (int di = -1; di <= 1; di++)
			{
				for (int dj = -1; dj <= 1; dj++)
				{
					int m = di + i;
					int n = dj + j;
					if (m >= 0 && m < height && n >= 0 && n < width)
					{
						gx_red += temp[m][n].rgbtRed * gx_array[di + 1][dj + 1];
						gy_red += temp[m][n].rgbtRed * gy_array[di + 1][dj + 1];
						gx_green += temp[m][n].rgbtGreen * gx_array[di + 1][dj + 1];
						gy_green += temp[m][n].rgbtGreen * gy_array[di + 1][dj + 1];
						gx_blue += temp[m][n].rgbtBlue * gx_array[di + 1][dj + 1];
						gy_blue += temp[m][n].rgbtBlue * gy_array[di + 1][dj + 1];
					}
				}
			}
			
			int combines_red = round(sqrt((gx_red * gx_red + gy_red * gy_red)));
			int combines_green = round(sqrt((gx_green * gx_green + gy_green * gy_green)));
			int combines_blue = round(sqrt((gx_blue * gx_blue + gy_blue * gy_blue)));
			
			if (combines_red > 255)
			{
				combines_red = 255;
			}
			if (combines_green > 255)
			{
				combines_green = 255;
			}
			if (combines_blue > 255)
			{
				combines_blue = 255;
			}
			
			image[i][j].rgbtRed = combines_red;
			image[i][j].rgbtGreen = combines_green;
			image[i][j].rgbtBlue = combines_blue;
		}
	}
	return;
}

