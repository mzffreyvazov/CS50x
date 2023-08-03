#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    int average_int = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // calculate the average
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = images[i][j].rgbtBlue;

            average_int = round((Green + Red + Blue)/3);


            // set the values to average
            image[i][j].rgbtBlue = average_int;
            image[i][j].rgbtGreen = average_int;
            image[i][j].rgbtRed = average_int;
        }
    }
    return;
}


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a temporary copy of original image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp[i][j] = image[i][j]

        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int totalRed, totalGreen, totalBlue;
            totalRed = totalGreen = totalBlue = 0;

            float counter = 0.00;

            for (int x = -1; x<2; x++) {
                for (int y = -1; y<2; y++) {
                    int currentX = i + x;
                    int currentY = i + y;

                    if (currentX < 0 || currentX > (height -1) || currentY < 0 || currentY > (width -1)) {
                        continue;
                    }
                    else {
                        totalRed += image[currentX][currentY].rgbtRed;
                        totalGreen += image[currentX][currentY].rgbtGreen;
                        totalBlue += image[currentX][currentY].rgbtBlue;

                        counter++;

                    }

                    temp[i][j],rgbtRed = round(totalRed / counter);
                    temp[i][j],rgbtGreen = round(totalGreen / counter);
                    temp[i][j],rgbtBlue = round(totalBlue / counter);

                }
            }


        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;


        }
    }





    return;
}