#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            float average = (image[row][col].rgbtBlue + image[row][col].rgbtRed + image[row][col].rgbtGreen) / 3.00;
            int avg = round(average);
            image[row][col].rgbtBlue = avg;
            image[row][col].rgbtRed = avg;
            image[row][col].rgbtGreen = avg;
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
            int newblue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            int newred = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int newgreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            
            image[i][j].rgbtBlue = (newblue > 255) ? 255 : newblue;
            image[i][j].rgbtRed = (newred > 255) ? 255 : newred;
            image[i][j].rgbtGreen = (newgreen > 255) ? 255 : newgreen;
            
        }
    }
    return;
}

// Reflect image horizontally
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumred = 0;
            int sumblue = 0;
            int sumgreen = 0;
            float count = 0.00;
            
            for (int di = -1; di < 2; di++)
            {
                for (int dj = -1; dj < 2; dj++)
                {
                    if (i + di < 0 || i + di > height - 1 || j + dj < 0 || j + dj > width - 1)
                    {
                        continue;
                    }
                    sumred += image[i + di][j + dj].rgbtRed;
                    sumblue += image[i + di][j + dj].rgbtBlue;
                    sumgreen += image[i + di][j + dj].rgbtGreen;
                
                    count++;
                }
            }
            
            copy[i][j].rgbtRed = round(sumred / count);
            copy[i][j].rgbtBlue = round(sumblue / count);
            copy[i][j].rgbtGreen = round(sumgreen / count);
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
        }
    }
    return;
}
