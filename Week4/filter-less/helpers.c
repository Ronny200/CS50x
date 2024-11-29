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
			round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
			image[i][j].rgbtBlue = gray;
			image[i][j].rgbtGreen = gray;
			image[i][j].rgbtRed = gray;
		}
	}
	return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
				.189 * image[i][j].rgbtBlue);
			int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
				.168 * image[i][j].rgbtBlue);
			int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
				.131 * image[i][j].rgbtBlue);
			if (sepiaRed > 255)
			{
				sepiaRed = 255;
			}
			if (sepiaGreen > 255)
			{
				sepiaGreen = 255;
			}
			if (sepiaBlue > 255)
			{
				sepiaBlue = 255;
			}
			image[i][j].rgbtRed = sepiaRed;
			image[i][j].rgbtGreen = sepiaGreen;
			image[i][j].rgbtBlue = sepiaBlue;
		}
	}
	return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			RGBTRIPLE temp = image[i][j];
			image[i][j] = image[i][width - 1 - j];
			image[i][width - 1 - j] = temp;
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
					int fi = di + i;
					int fj = dj + j;
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

