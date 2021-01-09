//
// Created by Dave on 1/9/21.
//

#include <iostream>
#include "screen_diamond.h"

namespace waveshare_eink_cpp
{

screen_diamond::screen_diamond() {}
screen_diamond::~screen_diamond() {}

void screen_diamond::draw(bitmap_image & img)
{
    std::cout << "screen_diamond::draw()\n";
    const uint8_t pixel_val {0}; // black

    // Display diamond in lower left
    const std::vector<std::vector<int>> diamond =
        {{0,0,0,0,1,0,0,0,0},
         {0,0,0,1,1,1,0,0,0},
         {0,0,1,1,1,1,1,0,0},
         {0,1,1,1,1,1,1,1,0},
         {1,1,1,1,1,1,1,1,1},
         {0,1,1,1,1,1,1,1,0},
         {0,0,1,1,1,1,1,0,0},
         {0,0,0,1,1,1,0,0,0},
         {0,0,0,0,1,0,0,0,0}};
    const size_t diamond_width = diamond.at(0).size(); // assume all the same
    const size_t diamond_height = diamond.size();

    for(size_t x = 0; x < diamond_width; ++x)
    {
        for(size_t y = 0; y < diamond_height; ++y)
        {
            const auto diamond_val = diamond.at(y).at(x);

            const size_t pixel_x = x;
            const size_t pixel_y = img.image_height_pixels() - diamond_height + y;

            if(0 != diamond_val)
            {
                img.set(pixel_x, pixel_y, pixel_val);
            }
        }
    }
}

}



