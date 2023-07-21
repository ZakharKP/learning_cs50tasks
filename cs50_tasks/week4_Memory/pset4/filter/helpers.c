#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Average
    float average, r, g, b;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            average = round((r + g + b) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //  swith horysontally
    RGBTRIPLE buffer;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width -1 -j; j++)
        {

            buffer = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // [9][9] average r g b
    RGBTRIPLE blured[height][width];
    float avR, avG, avB;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            avR = 0;
            avG = 0;
            avB = 0;

            int starti, startj, findHeight, findWidth;
            int pCount = 0;

            if(i == 0 || i == height - 1) {findHeight = 2;}
            else {findHeight = 3;}
            if(j == 0 || j == width - 1) {findWidth = 2;}
            else {findWidth = 3;}

            if(i == 0) {starti = i;}
            else {starti = i - 1;}

            if(j == 0) {startj = j;}
            else {startj = j - 1;}
            int h = starti;

            for(int x = 0; x < findHeight; x++)
            {
                int w = startj;
                for(int y = 0; y < findWidth; y++)
                {
                    avR = avR + image[h][w].rgbtRed;
                    avG = avG + image[h][w].rgbtGreen;
                    avB = avB + image[h][w].rgbtBlue;
                    pCount++;
                    w++;
                }
                h++;
            }
            avR = round(avR / pCount);
            avG = round(avG / pCount);
            avB = round(avB / pCount);
            blured[i][j].rgbtRed = avR;
            blured[i][j].rgbtGreen = avG;
            blured[i][j].rgbtBlue = avB;
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = blured[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gX[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    int gY[3][3] = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};
    RGBTRIPLE border, buffer;
    border.rgbtRed = 0;
    border.rgbtGreen = 0;
    border.rgbtBlue = 0;
    RGBTRIPLE edged[height][width];
    float r, g, b;
    int xRed, xGreen, xBlue, yRed, yGreen, yBlue;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            xRed = 0;
            xGreen = 0;
            xBlue = 0;
            yRed = 0;
            yGreen = 0;
            yBlue = 0;
            int h = i-1;
            for(int x = 0; x < 3; x++)
            {
                int w = j - 1;
                for(int y = 0; y < 3; y++)
                {
                    if(h < 0 || w < 0 || h >= height || w >= width)
                    {
                       buffer = border;
                    }
                    else
                    {
                        buffer = image[h][w];
                    }
                    xRed += buffer.rgbtRed * gX[x][y];
                    xGreen += buffer.rgbtGreen * gX[x][y];
                    xBlue += buffer.rgbtBlue * gX[x][y];
                    yRed += buffer.rgbtRed * gY[x][y];
                    yGreen += buffer.rgbtGreen * gY[x][y];
                    yBlue += buffer.rgbtBlue * gY[x][y];
                    w++;
                }
                h++;
            }



            r = xRed * xRed + yRed * yRed;
            g = xGreen * xGreen + yGreen * yGreen;
            b = xBlue * xBlue + yBlue * yBlue;
            if(r <= 0) r = 0;
            else r = round(sqrt(r));
            if(r >255) r = 255;

            if(g <= 0) g = 0;
            else g = round(sqrt(g));
            if(g >255) g = 255;

            if(b <= 0) b = 0;
            else b = round(sqrt(b));
            if(b >255) b = 255;
            edged[i][j].rgbtRed = r;
            edged[i][j].rgbtGreen = g;
            edged[i][j].rgbtBlue = b;
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = edged[i][j];
        }
    }
    return;
}
