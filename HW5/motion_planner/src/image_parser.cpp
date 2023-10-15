#include <iostream>
#include <fstream>
#include <vector>
#include "image_parser.h"

int main()
{
    const char *imageFilePath = "../test/image.png"; // Change to your image file path
    const int width = 400;                           // Change to your image width
    const int height = 400;

    image_parser maze(imageFilePath, width, height);

    // // Example: Access pixel value at row 10, column 20
    for (int x = 0; x < width; x++)
    {
        int pixelValue = maze.getPixelValue(0, x);
        printf("Pixel value at (0, %d): %d \n", x, static_cast<int>(pixelValue));
        // pixelValue = maze.getPixelValue(x, 0);
        // printf("Pixel value at (%d, 0): %d \n", x, static_cast<int>(pixelValue));
        // maze.updatePixel(0, x, 100);
    }

    // Specify the output PNG file name
    const char *outputFileName = "output_image.png";
    maze.writeImage(outputFileName);

    return 0;
}
