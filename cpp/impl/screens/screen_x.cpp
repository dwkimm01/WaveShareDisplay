//
// Created by Dave on 1/9/21.
//

#include <iostream>
#include "screen_x.h"

namespace waveshare_eink_cpp
{

screen_x::screen_x() {}
screen_x::~screen_x() {}

void screen_x::draw(bitmap_image & img)
{
    std::cout << "screen_square::draw()\n";
    const uint8_t pixel_val {0}; // black

    // Display X in upper right
    std::vector<std::vector<int>> xxx =
            {{1,1,0,0,0,0,0,1,1},
             {1,1,1,0,0,0,1,1,1},
             {0,1,1,1,0,1,1,1,0},
             {0,0,1,1,1,1,1,0,0},
             {0,0,0,1,1,1,0,0,0},
             {0,0,1,1,1,1,1,0,0},
             {0,1,1,1,0,1,1,1,0},
             {1,1,1,0,0,0,1,1,1},
             {1,1,0,0,0,0,0,1,1}};
    const size_t x_width = xxx.at(0).size(); // assume all the same
    const size_t x_height = xxx.size();

    for(size_t x = 0; x < x_width; ++x)
    {
        for(size_t y = 0; y < x_height; ++y)
        {
            const auto xxx_val = xxx.at(y).at(x);

            const size_t pixel_x = img.image_width_pixels() - x_width + x;
            const size_t pixel_y = 0; // img.image_height_pixels() - x_height + y;

            if(0 != xxx_val)
                img.set(pixel_x, pixel_y, pixel_val);
        }
    }
}

}
