//
// Created by Dave on 1/9/21.
//

#include <iostream>
#include <cmath>
#include <math.h>
#include "screen_bender.h"

namespace waveshare_eink_cpp
{

screen_bender::screen_bender() {}

screen_bender::~screen_bender() {}

void screen_bender::draw(bitmap_image & img)
{
    std::cout << "screen_circle::draw()\n";

//    const double x_center {5.0};
//    const double y_center {5.0};
//    const double radius {5.0};
    const uint8_t pixel_val {0}; // black

    const size_t max_x {img.image_width_pixels()};
    const size_t max_y {img.image_height_pixels()};

    const size_t teeth_rows {3};
    const size_t teeth_cols {4};


    // Columns
    const int teeth_col_step = max_x * 1.0 / teeth_cols;
    for(int teeth_col = 0; teeth_col < teeth_cols; ++teeth_col)
    {
        int pixel_x = (teeth_col+1) * teeth_col_step;
        for(int pixel_y = 0; pixel_y < max_y; ++pixel_y)
        {
            img.set(pixel_x, pixel_y, pixel_val);
        }
    }

    // Rows
    const int teeth_row_step = max_y * 1.0 / teeth_rows;
    for(int teeth_row = 0; teeth_row < teeth_rows; ++ teeth_row)
    {
        int pixel_y = (teeth_row+1) * teeth_row_step;
        for(int pixel_x = 0; pixel_x < max_x; ++pixel_x)
        {
            img.set(pixel_x, pixel_y, pixel_val);
        }
    }


}

}
