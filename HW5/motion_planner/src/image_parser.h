#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "lodepng.h"

class image_parser
{
public:
    image_parser(const std::string &imageFilePath, int width, int height) : width_(width), height_(height)
    {
        // const int width = 400;  // Change to your image width
        // const int height = 400; // Change to your image height

        // Open the image file for binary reading
        std::ifstream imageFile(imageFilePath, std::ios::binary);

        assert(imageFile && "Error: Unable to open the image file.");

        // Create a 2D array to store pixel values
        imageArray_.resize(height);

        // Read pixel values from the image file into the array
        for (int y = 0; y < height; y++)
        {
            imageArray_[y].resize(width);
            for (int x = 0; x < width; x++)
            {
                uint8_t pixelValue;
                imageFile.read(reinterpret_cast<char *>(&pixelValue), sizeof(uint8_t));
                imageArray_[y][x] = pixelValue;
            }
        }

        // Close the image file
        imageFile.close();
    }

    int getPixelValue(int y, int x)
    {
        return imageArray_[y][x];
    }

    void updatePixel(int y, int x, uint8_t val)
    {
        imageArray_[y][x] = val;
    }

    void writeImage(const char *outputFileName)
    {
        // Encode the imageArray and write it to a PNG file using LodePNG
        std::vector<uint8_t> pngData;
        unsigned error = lodepng::encode(pngData, reinterpret_cast<const unsigned char *>(imageArray_.data()),
                                         width_, height_, LCT_GREY);
        lodepng::save_file(pngData, outputFileName);
    }

private:
    std::vector<std::vector<uint8_t>> imageArray_;
    int width_, height_;
};
