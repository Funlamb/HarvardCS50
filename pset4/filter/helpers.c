#include <helpers.h>
#include "stdio.h"
#include "math.h"

int capNum(int original, int low, int high); //helps with capping numbers

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //make nested for loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //go through all pixels and get their RGB color
            BYTE r = image[i][j].rgbtRed;
            BYTE g = image[i][j].rgbtGreen;
            BYTE b = image[i][j].rgbtBlue;

            //average those colors to get grayscale.
            float av = (r + g + b) / 3.0;
            int average = round(av);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //make a nested loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get all colors
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;
            //turn each pixel into sepie
            int low = 0;
            int high = 255;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaRed = capNum(sepiaRed, low, high);
            image[i][j].rgbtRed = sepiaRed;

            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaGreen = capNum(sepiaGreen, low, high);
            image[i][j].rgbtGreen = sepiaGreen;

            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            sepiaBlue = capNum(sepiaBlue, low, high);
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

int capNum(int original, int low, int high)
{
    //return high if high
    if (original > high)
    {
        return high;
    }
    //return low if low
    else if (original < low)
    {
        return low;
    }
    //return original if in range
    return original;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //find the center of the image
    int center = width / 2;
    //create a nested loop to go horizontally
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < center; j++)
        {
            //stop at middle
            //work inward
            //get the first pixel in memory
            BYTE firstRed = image[i][j].rgbtRed;
            BYTE firstGreen = image[i][j].rgbtGreen;
            BYTE firstBlue = image[i][j].rgbtBlue;
            //get last pixel in memory
            BYTE secondRed = image[i][width - j - 1].rgbtRed;
            BYTE secondGreen = image[i][width - j - 1].rgbtGreen;
            BYTE secondBlue = image[i][width - j - 1].rgbtBlue;

            //flip those two pixel
            image[i][j].rgbtRed = secondRed;
            image[i][j].rgbtGreen = secondGreen;
            image[i][j].rgbtBlue = secondBlue;

            image[i][width - j - 1].rgbtRed = firstRed;
            image[i][width - j - 1].rgbtGreen = firstGreen;
            image[i][width - j - 1].rgbtBlue = firstBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //use the copy to change the image
    int numberOfPixels = 0;
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    //create nested for loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("I: %i J: %i\n", i, j);
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (k + i >= 0 && k + i <= height - 1 && l + j >= 0 && l + j <= width - 1)
                    {
                        // printf("   k: %i l: %i\n",k+i, l+j );
                        red += copy[i + k][j + l].rgbtRed;
                        green += copy[i + k][j + l].rgbtGreen;
                        blue += copy[i + k][j + l].rgbtBlue;
                        numberOfPixels++;
                    }
                }
            }
            image[i][j].rgbtRed = round(red / (float) numberOfPixels);
            image[i][j].rgbtGreen = round(green / (float) numberOfPixels);
            image[i][j].rgbtBlue = round(blue / (float) numberOfPixels);
            numberOfPixels = 0;
            red = 0.0f;
            green = 0.0f;
            blue = 0.0f;
        }
    }
    return;
}