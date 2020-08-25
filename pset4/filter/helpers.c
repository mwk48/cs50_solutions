#include "helpers.h"
#include <math.h>
// Convert image to grayscale
int ComputeRed(int sumRed, int sumRed2);
int ComputeGreen(int sumGreen, int sumGreen2);
int ComputeBlue(int sumBlue, int sumBlue2);
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
    int count=0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y <2; y++)
                {
                    if ( ! (x+i<0 || y+j<0 || x+i>checklow || y+j>checkright) )
                    {
                           sumBlue +=image[i+x][j+y].rgbtBlue;
                           sumGreen +=image[i+x][j+y].rgbtGreen;
                           sumRed +=image[i+x][j+y].rgbtRed;
                           count+=1;
                    }
                }
            }
            temp[i][j].rgbtRed = round(sumRed / (float) count);
            temp[i][j].rgbtGreen = round(sumGreen / (float) count);
            temp[i][j].rgbtBlue = round(sumBlue / (float) count);
            sumRed=0;
            sumBlue=0;
            sumGreen=0;
            count=0;
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
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
    int sumRed2=0, sumGreen2=0, sumBlue2=0;
    int checkup=0;
    int checklow=height-1;
    int checkleft=0;
    int checkright=width-1;
    int gx[3][3]={ { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    int gy[3][3]={ { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            if(i==checkup)
            {
                if(j==checkleft)
                {
                    for (int x = i, cox=0; x < i+2; x++,cox++)
                    {
                        for (int y = j, coy=0; y <j+2; y++,coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[1+cox][1+coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[1+cox][1+coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[1+cox][1+coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[1+cox][1+coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[1+cox][1+coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[1+cox][1+coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
                else if (j==checkright)
                {
                    for (int x = i, cox=0; x < i+2; x++,cox++)
                    {
                        for (int y = j, coy=0; y >j-2; y--,coy--)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[1+cox][1-coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[1+cox][1-coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[1+cox][1-coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[1+cox][1-coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[1+cox][1-coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[1+cox][1-coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
                else
                {
                    for (int x = i, cox=0; x < i+2; x++,cox++)
                    {
                        for (int y = j-1, coy=0; y <j+2; y++,coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[1+cox][coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[1+cox][coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[1+cox][coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[1+cox][coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[1+cox][coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[1+cox][coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
            }
            else if(i==checklow)
            {
                if(j==checkleft)
                {
                    for (int x = i, cox=0; x > i-2; x--,cox++)
                    {
                        for (int y = j, coy=0; y <j+2; y++,coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[1-cox][1+coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[1-cox][1+coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[1-cox][1+coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[1-cox][1+coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[1-cox][1+coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[1-cox][1+coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
                else if (j==checkright)
                {
                    for (int x = i, cox=0; x > i-2; x--,cox++)
                    {
                        for (int y = j, coy=0; y >j-2; y--,coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[1-cox][1-coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[1-cox][1-coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[1-cox][1-coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[1-cox][1-coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[1-cox][1-coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[1-cox][1-coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
                else
                {
                    for (int x = i, cox=0; x > i-2; x--,cox++)
                    {
                        for (int y = j-1, coy=0; y <j+2; y++,coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[1-cox][coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[1-cox][coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[1-cox][coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[1-cox][coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[1-cox][coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[1-cox][coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
            }
            else
            {
                if(j==checkleft)
                {
                    for (int x = i-1, cox=0; x < i+2; x++, cox++)
                    {
                        for (int y = j, coy=0; y <j+2; y++, coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[cox][1+coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[cox][1+coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[cox][1+coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[cox][1+coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[cox][1+coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[cox][1+coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
                else if (j==checkright)
                {
                    for (int x = i-1, cox=0; x < i+2; x++, cox++)
                    {
                        for (int y = j, coy=0; y >j-2; y--, coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[cox][1-coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[cox][1-coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[cox][1-coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[cox][1-coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[cox][1-coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[cox][1-coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
                else
                {
                    for (int x = i-1, cox=0; x < i+2; x++, cox++)
                    {
                        for (int y = j-1, coy=0; y <j+2; y++, coy++)
                        {
                            sumRed+=temp[x][y].rgbtRed*gx[cox][coy];
                            sumRed2+=temp[x][y].rgbtRed*gy[cox][coy];
                            sumGreen+=temp[x][y].rgbtGreen*gx[cox][coy];
                            sumGreen2+=temp[x][y].rgbtGreen*gy[cox][coy];
                            sumBlue+=temp[x][y].rgbtBlue*gx[cox][coy];
                            sumBlue2+=temp[x][y].rgbtBlue*gy[cox][coy];
                        }
                    }
                    image[i][j].rgbtRed = ComputeRed(sumRed,sumRed2);
                    image[i][j].rgbtGreen = ComputeGreen(sumGreen, sumGreen2);
                    image[i][j].rgbtBlue = ComputeBlue(sumBlue, sumBlue2);
                }
            }
            sumRed=0;
            sumBlue=0;
            sumGreen=0;
            sumRed2=0;
            sumBlue2=0;
            sumGreen2=0;
        }
    }
    return;
}
int ComputeRed(int sumRed, int sumRed2)
{
    int resultRed=round(sqrt(sumRed*sumRed+sumRed2*sumRed2));
    if (resultRed>=255)
    {
        resultRed=255;
    }
    return resultRed;
}
int ComputeGreen(int sumGreen, int sumGreen2)
{
    int resultGreen=round(sqrt(sumGreen*sumGreen+sumGreen2*sumGreen2));
    if (resultGreen>=255)
    {
        resultGreen=255;
    }
    return resultGreen;
}
int ComputeBlue(int sumBlue, int sumBlue2)
{
    int resultBlue=round(sqrt(sumBlue*sumBlue+sumBlue2*sumBlue2));
    if (resultBlue>=255)
    {
        resultBlue=255;
    }
    return resultBlue;
}
