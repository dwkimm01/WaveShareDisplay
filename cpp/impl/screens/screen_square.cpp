//
// Created by Dave on 1/9/21.
//

#include <iostream>
#include "screen_square.h"

namespace waveshare_eink_cpp
{

screen_square::screen_square() {}
screen_square::~screen_square() {}

void screen_square::draw(bitmap_image & img)
{
    std::cout << "screen_square::draw()\n";
    const uint8_t pixel_val {0}; // black
    // Display box in lower right
    for(size_t x = img.image_width_pixels()-10; x < img.image_width_pixels(); ++x)
    {
        for(size_t y = img.image_height_pixels()-10; y < img.image_height_pixels(); ++y)
        {
            img.set(x, y, pixel_val);
        }
    }
}

}
