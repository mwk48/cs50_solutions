#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    int sum;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            sum=image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed;
            average=round(sum/3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            if (sepiaGreen>255)
            {
                sepiaGreen=255;
            }
            if (sepiaBlue>255)
            {
                sepiaBlue=255;
            }
            if (sepiaRed>255)
            {
                sepiaRed=255;
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
    int checkw=0;
    int checkw2=width-1;
    int checkh=0;
    int temp1,temp2,temp3;
    while (1)
    {
        if (checkh>=height)
        {
            break;
        }
        while (1)
        {
            if (checkw2<=checkw)
            {
                break;
            }
            temp1=image[checkh][checkw].rgbtRed;
            temp2=image[checkh][checkw].rgbtGreen;
            temp3=image[checkh][checkw].rgbtBlue;
            image[checkh][checkw].rgbtRed=image[checkh][checkw2].rgbtRed;
            image[checkh][checkw].rgbtGreen=image[checkh][checkw2].rgbtGreen;
            image[checkh][checkw].rgbtBlue=image[checkh][checkw2].rgbtBlue;
            image[checkh][checkw2].rgbtRed=temp1;
            image[checkh][checkw2].rgbtGreen=temp2;
            image[checkh][checkw2].rgbtBlue=temp3;
            checkw+=1;
            checkw2-=1;
        }
        checkw=0;
        checkw2=width-1;
        checkh+=1;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
           temp[i][j].rgbtBlue =image[i][j].rgbtBlue;
           temp[i][j].rgbtGreen =image[i][j].rgbtGreen;
           temp[i][j].rgbtRed =image[i][j].rgbtRed;
        }
    }
    int sumRed=0, sumGreen=0, sumBlue=0;
    int checkup=0;
    int checklow=height-1;
    int checkleft=0;
    int checkright=width-1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            if(i==checkup)
            {
                if(j==checkleft)
                {
                    for (int x = i; x < i+2; x++)
                    {
                        for (int y = j; y <j+2; y++)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/4.0);
                    temp[i][j].rgbtGreen = round(sumGreen/4.0);
                    temp[i][j].rgbtBlue = round(sumBlue/4.0);
                }
                else if (j==checkright)
                {
                    for (int x = i; x < i+2; x++)
                    {
                        for (int y = j; y >j-2; y--)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/4.0);
                    temp[i][j].rgbtGreen = round(sumGreen/4.0);
                    temp[i][j].rgbtBlue = round(sumBlue/4.0);
                }
                else
                {
                    for (int x = i; x < i+2; x++)
                    {
                        for (int y = j-1; y <j+2; y++)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/6.0);
                    temp[i][j].rgbtGreen = round(sumGreen/6.0);
                    temp[i][j].rgbtBlue = round(sumBlue/6.0);
                }
            }
            else if(i==checklow)
            {
                if(j==checkleft)
                {
                    for (int x = i; x > i-2; x--)
                    {
                        for (int y = j; y <j+2; y++)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/4.0);
                    temp[i][j].rgbtGreen = round(sumGreen/4.0);
                    temp[i][j].rgbtBlue = round(sumBlue/4.0);
                }
                else if (j==checkright)
                {
                    for (int x = i; x > i-2; x--)
                    {
                        for (int y = j; y >j-2; y--)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/4.0);
                    temp[i][j].rgbtGreen = round(sumGreen/4.0);
                    temp[i][j].rgbtBlue = round(sumBlue/4.0);
                }
                else
                {
                    for (int x = i; x > i-2; x--)
                    {
                        for (int y = j-1; y <j+2; y++)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/6.0);
                    temp[i][j].rgbtGreen = round(sumGreen/6.0);
                    temp[i][j].rgbtBlue = round(sumBlue/6.0);
                }
            }
            else
            {
                if(j==checkleft)
                {
                    for (int x = i-1; x < i+2; x++)
                    {
                        for (int y = j; y <j+2; y++)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/6.0);
                    temp[i][j].rgbtGreen = round(sumGreen/6.0);
                    temp[i][j].rgbtBlue = round(sumBlue/6.0);
                }
                else if (j==checkright)
                {
                    for (int x = i-1; x < i+2; x++)
                    {
                        for (int y = j; y >j-2; y--)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/6.0);
                    temp[i][j].rgbtGreen = round(sumGreen/6.0);
                    temp[i][j].rgbtBlue = round(sumBlue/6.0);
                }
                else
                {
                    for (int x = i-1; x < i+2; x++)
                    {
                        for (int y = j-1; y <j+2; y++)
                        {
                            sumRed+=image[x][y].rgbtRed;
                            sumGreen+=image[x][y].rgbtGreen;
                            sumBlue+=image[x][y].rgbtBlue;
                        }
                    }
                    temp[i][j].rgbtRed = round(sumRed/9.0);
                    temp[i][j].rgbtGreen = round(sumGreen/9.0);
                    temp[i][j].rgbtBlue = round(sumBlue/9.0);
                }
            }
            sumRed=0;
            sumBlue=0;
            sumGreen=0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
           image[i][j].rgbtBlue =temp[i][j].rgbtBlue;
           image[i][j].rgbtGreen =temp[i][j].rgbtGreen;
           image[i][j].rgbtRed =temp[i][j].rgbtRed;
        }
    }
    return;
}