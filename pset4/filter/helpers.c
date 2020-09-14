#include "helpers.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	//for each row in image
	for (int i = 0; i < height; i++)
	{
		//for each colum in image
		for (int j = 0; j < width; j++)
		{
			//gray value is average of all three color values
			float gray_value_float = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
			BYTE gray_value = round(gray_value_float);

			image[i][j].rgbtBlue = gray_value;
			image[i][j].rgbtGreen = gray_value;
			image[i][j].rgbtRed = gray_value;
		}
	}
    return;
}

//swap elements
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
	RGBTRIPLE temp = *pixel1;
	*pixel1 = *pixel2;
	*pixel2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	//temp var
	RGBTRIPLE tmp_image[height][width];
	memcpy(tmp_image, *image, height*width*3);

	//for each row in image
	for (int i = 0; i < height; i++)
	{
		//for each column in image
		for (int j = 0; j < width / 2; j++)
		{
			//swap element at opposite end of array
			swap(&image[i][j], &image[i][width - j - 1]);
		}
	}
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

	//temp var
	RGBTRIPLE tmp_image[height][width];
	memcpy(tmp_image, *image, height*width*3);

	//for each row in image
	for (int i = 0; i < height; i++)
	{
		//for each column in image
		for (int j = 0; j < width; j++)
		{
			//reset values for each pixel
			int red_sum = 0;
			int blue_sum = 0;
			int green_sum = 0;
			int grid_size = 0;

			//for each row in 3x3 grid around [i][j]
			for (int k = i - 1; k <= i + 1; k++)
			{
				//if k is out of bounds, skip iteration
				if (k < 0 || k > height - 1)
				{
					continue;
				}

				//for each column in 3x3 grid around [i][j]
				for (int l = j - 1; l <= j + 1; l++)
				{
					//if l is out of bounds, skip iteration
					if (l < 0 || l > width - 1)
					{
						continue;
					}

					//add red value of current pixel to sum of red values
					red_sum += tmp_image[k][l].rgbtRed;
					//add green value of current pixel to sum of green values
					green_sum += tmp_image[k][l].rgbtGreen;
					//add blue value of current pixel to sum of blue values
					blue_sum += tmp_image[k][l].rgbtBlue;
					//iterate grid size
					grid_size++;
				}
			}

			//assign new values based on averages of 3x3 grid
			image[i][j].rgbtRed = round((float) red_sum / grid_size);
			image[i][j].rgbtGreen = round((float) green_sum / grid_size);
			image[i][j].rgbtBlue = round((float) blue_sum / grid_size);
		}
	}

    return;
}

//limits color value to 255
int limit(int value)
{
	//if value < 255, return value, else return 255
	return value < 255 ? value: 255;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	//sobel kernels
	int gx_weight[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int gy_weight[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


	//temp var
	RGBTRIPLE tmp_image[height][width];
	memcpy(tmp_image, *image, height*width*3);

	//loop for each pixel row in image
	for (int i = 0; i < height; i++)
	{
		//loop for each pixel column in image
		for (int j = 0; j < width; j++)
		{
			//reset gx and gy values for each grid
			int gx_red_sum = 0, gy_red_sum = 0;
			int gx_green_sum = 0, gy_green_sum = 0;
			int gx_blue_sum = 0, gy_blue_sum = 0;

			//for each row in 3x3 grid
			for (int a = -1; a <= 1; a++)
			{
				//if pixel is out of bounds
				if (i + a < 0 || i + a > height - 1)
				{
					continue;
				}

				//for each column in 3x3 grid
				for (int b = -1; b <= 1; b++)
				{
					//if pixel is out of bounds
					if (j + b < 0 || j + b > width - 1)
					{
						continue; 
					}

					//compute for gx
					gx_red_sum += gx_weight[a + 1][b + 1] * tmp_image[i + a][j + b].rgbtRed;
					gx_green_sum += gx_weight[a + 1][b + 1] * tmp_image[i + a][j + b].rgbtGreen;
					gx_blue_sum += gx_weight[a + 1][b + 1] * tmp_image[i + a][j + b].rgbtBlue;

					//compute for gy
					gy_red_sum += gy_weight[a + 1][b + 1] * tmp_image[i + a][j + b].rgbtRed;
					gy_green_sum += gy_weight[a + 1][b + 1] * tmp_image[i + a][j + b].rgbtGreen;
					gy_blue_sum += gy_weight[a + 1][b + 1] * tmp_image[i + a][j + b].rgbtBlue;
				}
			}

			//assign new values of gx and gy based on pythagorean theorem and limit them to 255
			image[i][j].rgbtRed = limit(round(sqrt(gx_red_sum*gx_red_sum + gy_red_sum*gy_red_sum)));
			image[i][j].rgbtGreen = limit(round(sqrt(gx_green_sum*gx_green_sum + gy_green_sum*gy_green_sum)));
			image[i][j].rgbtBlue = limit(round(sqrt(gx_blue_sum*gx_blue_sum + gy_blue_sum*gy_blue_sum)));
		}
	}
    return;
}
