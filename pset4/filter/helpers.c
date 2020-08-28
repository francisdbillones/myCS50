#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float gray_value_float = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
			BYTE gray_value = round(gray_value_float);
			image[i][j].rgbtBlue = gray_value;
			image[i][j].rgbtGreen = gray_value;
			image[i][j].rgbtRed = gray_value;
		}
	}
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tmp_image = image;
			image[i][j] = tmp_image[i][width - j];
		}
	}
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	int red_sum = 0;
	int blue_sum = 0;
	int green_sum = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = i - 1; k <= i + 1; k++)
			{
				if (k < 0 || k > height - 1)
				{
					continue;
				}

				for (int l = j - 1; l <= j; l++)
				{
					if (l < 0 || l > width - 1)
					{
						continue;
					}

					red_sum += image[k][l].rgbtRed;
					green_sum += image[k][l].rgbtGreen;
					blue_sum += image[k][l].rgbtBlue;
				}
			}

		}
	}
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	
    return;
}
