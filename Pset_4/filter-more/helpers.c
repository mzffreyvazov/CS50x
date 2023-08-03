#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;
    int average_int = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // calculate the average
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;

            average = (Red + Green + Blue) / 3;
            average_int = round(average);

            // set the values to average
            image[i][j].rgbtBlue = average_int;
            image[i][j].rgbtGreen = average_int;
            image[i][j].rgbtRed = average_int;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = (int) (width / 2);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < middle; j++) {

            // for Blue
            int tmp_b = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][(width - j - 1)].rgbtBlue;
            image[i][(width - j - 1)].rgbtBlue = tmp_b;

            // for Green
            int tmp_g = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][(width - j - 1)].rgbtGreen;
            image[i][(width - j - 1)].rgbtGreen = tmp_g;

            // for Red
            int tmp_r = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][(width - j - 1)].rgbtRed;
            image[i][(width - j - 1)].rgbtRed = tmp_r;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp[i][j] = image[i][j];

        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int in_boundry_pixel_number = 0;
            float red_sum = 0;
            float green_sum = 0;
            float blue_sum = 0;

            // looping through the kernel
            for (int kx = 0; kx < 3; kx++) {
                for (int ky = 0; ky < 3; ky++) {
                    // find the coordinate of the pixel inside of the kernel
                    int pixel_i = i + kx - 1;
                    int pixel_j = j + ky - 1;
                    if (pixel_i < 0 || pixel_i >= height || pixel_j < 0 || pixel_j >= width) {
                        continue;
                    }
                    else {
                        in_boundry_pixel_number++;

                        red_sum += temp[pixel_i][pixel_j].rgbtRed;
                        green_sum += temp[pixel_i][pixel_j].rgbtGreen;
                        blue_sum += temp[pixel_i][pixel_j].rgbtBlue;
                    }

                }
            }
            // after looping through the kernel, we set the inital pixel's RGB values to the average of the sums we calculated
            // calculating the average for each colors
            int average_red_sum = round(red_sum / in_boundry_pixel_number);
            int average_green_sum = round(green_sum / in_boundry_pixel_number);
            int average_blue_sum = round(blue_sum / in_boundry_pixel_number);

            // set the RGB values of the images's pixels to the averaged sum
            image[i][j].rgbtRed = average_red_sum;
            image[i][j].rgbtGreen = average_green_sum;
            image[i][j].rgbtBlue = average_blue_sum;

        }

    }
    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create the kernels for x and y directions (Gx and Gy)
    int kernel_gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int kernel_gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // create a copy of image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp[i][j] = image[i][j];

        }
    }

    // loop through the each pixel of the image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // sum of the products of RGB values and kernel values
            float red_sum_gx = 0.0;
            float red_sum_gy = 0.0;
            float green_sum_gx = 0.0;
            float green_sum_gy = 0.0;
            float blue_sum_gx = 0.0;
            float blue_sum_gy = 0.0;

            // final values for each pixel
            int red_sum_final = 0;
            int green_sum_final = 0;
            int blue_sum_final = 0;

            // looping through the kernel
            for (int kx = 0; kx < 3; kx++) {
                for (int ky = 0; ky < 3; ky++) {

                    int pixel_i = i + kx - 1;
                    int pixel_j = j + ky - 1;

                    if (pixel_i < 0 || pixel_i >= height || pixel_j < 0 || pixel_j >= width) {
                        continue;
                    }
                    else {
                        // calculate the Gx
                        red_sum_gx += kernel_gx[kx][ky] * temp[pixel_i][pixel_j].rgbtRed;
                        green_sum_gx += kernel_gx[kx][ky] * temp[pixel_i][pixel_j].rgbtGreen;
                        blue_sum_gx += kernel_gx[kx][ky] * temp[pixel_i][pixel_j].rgbtBlue;

                        // calculate the Gy
                        red_sum_gy += kernel_gy[kx][ky] * temp[pixel_i][pixel_j].rgbtRed;
                        green_sum_gy += kernel_gy[kx][ky] * temp[pixel_i][pixel_j].rgbtGreen;
                        blue_sum_gy += kernel_gy[kx][ky] * temp[pixel_i][pixel_j].rgbtBlue;


                    }


                }
            }

            red_sum_final = round(sqrt((red_sum_gx * red_sum_gx) + (red_sum_gy * red_sum_gy)));
            green_sum_final = round(sqrt((green_sum_gx * green_sum_gx) + (green_sum_gy * green_sum_gy)));
            blue_sum_final = round(sqrt((blue_sum_gx * blue_sum_gx) + (blue_sum_gy * blue_sum_gy)));

            //condition for gx or gy being above 255
            red_sum_final = red_sum_final > 255 ? 255 : red_sum_final;
            blue_sum_final = blue_sum_final > 255 ? 255 : blue_sum_final;
            green_sum_final = green_sum_final > 255 ? 255 : green_sum_final;

            // change the original pixel values with the new G values
            image[i][j].rgbtRed = red_sum_final;
            image[i][j].rgbtGreen = green_sum_final;
            image[i][j].rgbtBlue = blue_sum_final;
        }

    }

    return;
}
