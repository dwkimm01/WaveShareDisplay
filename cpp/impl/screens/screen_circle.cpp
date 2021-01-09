//
// Created by Dave on 1/9/21.
//

#include <iostream>
#include <cmath>
#include <math.h>
#include "screen_circle.h"

namespace waveshare_eink_cpp
{

screen_circle::screen_circle()
{
}

screen_circle::~screen_circle() {}

void screen_circle::draw(bitmap_image & img)
{
    std::cout << "screen_circle::draw()\n";
    // Display circle in upper left
    for(size_t x = 0; x < 10; ++x)
    {
        for(size_t y = 0; y < 10; ++y)
        {
            const double x_center {5.0};
            const double y_center {5.0};
            const double radius {5.0};

            if(radius > sqrt(
                    pow(x_center - x, 2) + pow(y_center - y, 2)
            ))
            {
                img.set(x, y, 1);
            }
        }
    }

}

}
