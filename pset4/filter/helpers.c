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
	RGBTRIPLE tmp_image[height][width];
	
	//copy elements
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tmp_image[i][j].rgbtRed = image[i][j].rgbtRed;
			tmp_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
			tmp_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
		}
	}

	//for each row in image
	for (int i = 0; i < height; i++)
	{
		//for each column in image
		for (int j = 0; j < width; j++)
		{
			//copy element at opposite end of array
			image[i][j].rgbtRed = tmp_image[i][width - j - 1].rgbtRed;
			image[i][j].rgbtGreen = tmp_image[i][width - j - 1].rgbtGreen;
			image[i][j].rgbtBlue = tmp_image[i][width - j - 1].rgbtBlue;
			
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
	int grid_size = 0;
	RGBTRIPLE tmp_image[height][width];
	memcpy(tmp_image, image, sizeof(*image));

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

					red_sum += tmp_image[k][l].rgbtRed;
					green_sum += tmp_image[k][l].rgbtGreen;
					blue_sum += tmp_image[k][l].rgbtBlue;
					grid_size++;
				}
			}

			image[i][j].rgbtRed = round((float) red_sum / grid_size);
			image[i][j].rgbtGreen = round((float) green_sum / grid_size);
			image[i][j].rgbtBlue = round((float) blue_sum / grid_size);
		}
	}
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	//gx and gy values
	int gx_red_sum = 0, gy_red_sum = 0;
	int gx_green_sum = 0, gy_green_sum = 0;
	int gx_blue_sum = 0, gy_blue_sum = 0;

	//temp var for image
	RGBTRIPLE tmp_image[height][width];
	memcpy(tmp_image, image, sizeof(*image));

	//loop for each pixel row in image
	for (int i = 0; i < height; i++)
	{
		//loop for each pixel column in image
		for (int j = 0; j < width; j++)
		{
			//loop for each row in 3x3 grid
			for (int k = i - 1; k <= i + 1; k++)
			{
				//checks to see if pixel is beyond border
				if (k < 0 || k > height)
				{
					continue;
				}

				//loop for each column in 3x3 grid
				for (int l = j - 1; l <= j + 1; l++)
				{
					//checks to see if pixel is beyond border
					if (l < 0 || l > width)
					{
						continue;
					}

					//if pixel is on top or bottom row
					if (k == i - 1 || k == i + 1)
					{
						//if pixel is on left or right side
						if (l == j - 1 || l == j + 1)
						{
							//if pixel is on left
							if (l == j - 1)
							{
								//compute for gx accordingly
								gx_red_sum += -1 * tmp_image[k][l].rgbtRed;
								gx_blue_sum += -1 * tmp_image[k][l].rgbtBlue;
								gx_green_sum += -1 * tmp_image[k][l].rgbtGreen;
							}

							//else pixel is on right
							else
							{
								//compute for gx accordingly
								gx_red_sum += tmp_image[k][l].rgbtRed;
								gx_blue_sum += tmp_image[k][l].rgbtBlue;
								gx_green_sum += tmp_image[k][l].rgbtGreen;
							}

							//compute for gy accordingly
							gy_red_sum += -1 * tmp_image[k][l].rgbtRed;
							gy_green_sum += -1 * tmp_image[k][l].rgbtGreen;
							gy_blue_sum += -1 * tmp_image[k][l].rgbtBlue;
						}
						
						//else pixel is in middle column
						else
						{
							//if pixel is on top row
							if (k == i - 1)
							{
								//compute for gy accordingly
								gy_red_sum += -2 * tmp_image[k][l].rgbtRed;
								gy_green_sum += -2 * tmp_image[k][l].rgbtGreen;
								gy_blue_sum += -2 * tmp_image[k][l].rgbtBlue;
							}

							//else pixel is in bottom row
							else
							{
								gy_red_sum += 2 * tmp_image[k][l].rgbtRed;
								gy_green_sum += 2 * tmp_image[k][l].rgbtGreen;
								gy_blue_sum += 2 * tmp_image[k][l].rgbtBlue;
							}
						}
					}

					//else pixel is in middle row
					else
					{
						//if pixel is on left column
						if (l == j - 1)
						{
							gx_red_sum += -2 * tmp_image[k][l].rgbtRed;
							gx_green_sum += -2 * tmp_image[k][l].rgbtGreen;
							gx_blue_sum += -2 * tmp_image[k][l].rgbtBlue;
						}

						//else if pixel is on right column
						else if (l == j + 1)
						{
							gx_red_sum += 2 * tmp_image[k][l].rgbtRed;
							gx_green_sum += 2 * tmp_image[k][l].rgbtGreen;
							gx_blue_sum += 2 * tmp_image[k][l].rgbtBlue;
						}
					}
				}
			}

			int red_pixel_val = sqrt(((gx_red_sum)*(gx_red_sum)) + ((gy_red_sum)*(gy_red_sum)));
			int blue_pixel_val = sqrt(((gx_blue_sum)*(gx_blue_sum)) + ((gy_blue_sum)*(gy_blue_sum)));
			int green_pixel_val = sqrt(((gx_green_sum)*(gx_green_sum)) + ((gy_green_sum)*(gy_green_sum)));

			//if pixel val is greater than 255, cap color value at 255
			if (red_pixel_val > 255)
			{
				image[i][j].rgbtRed = 255;
			}

			//else pixel value is less than or equal to 255
			else
			{
				image[i][j].rgbtRed = red_pixel_val;
			}

			//if pixel val is greater than 255, cap color value at 255
			if (green_pixel_val > 255)
			{
				image[i][j].rgbtGreen = 255;
			}

			//else pixel value is less than or equal to 255
			else
			{
				image[i][j].rgbtGreen = green_pixel_val;
			}

			//if pixel val is greater than 255, cap color value at 255
			if (blue_pixel_val > 255)
			{
				image[i][j].rgbtBlue = 255;
			}

			//else pixel value is less than or equal to 255
			else
			{
				image[i][j].rgbtBlue = blue_pixel_val;
			}
		}

	}
    return;
}
