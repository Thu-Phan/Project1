#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"
#include <math.h>

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *sub(unsigned char *background, unsigned char *girl, unsigned char *new_bg, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < channel; k++)
            {
                int t = i * width * channel + j * channel + k;
                if (

                    abs((background[t]) - girl[t]) > 21 // reduce noise
                )
                {
   
                    temp_array[t] = girl[t];
                }
                else
                {
                    temp_array[t] = new_bg[t];
                }

            }
        }
    }
    return temp_array;
}
int main()
{
    // declare variables
    int width, height, channel = 3;
    char path_img1[] = "./images/background.jpg";
    char path_img2[] = "./images/foreground.jpg";

    char path_img3[] = "./images/new_background.jpg";

    char save_path[] = "./images/foreground-New.jpg";

    // read image data
    unsigned char *background = stbi_load(path_img1, &width, &height, &channel, 0);
    if (background == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    unsigned char *girl = stbi_load(path_img2, &width, &height, &channel, 0);
    if (girl == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }

    unsigned char *new_bg = stbi_load(path_img3, &width, &height, &channel, 0);
    if (new_bg == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }

    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);

    unsigned char *image = sub(background, girl, new_bg, width, height, channel);

    // save image
    stbi_write_jpg(save_path, width, height, channel, image, width * channel);
    printf("New image saved to %s\n", save_path);
}