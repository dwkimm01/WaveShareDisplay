//
// Created by Dave on 1/10/21.
//

#include <iostream>
#include "widget_bitmap.h"

namespace waveshare_eink_cpp
{

widget_bitmap::widget_bitmap() {}
widget_bitmap::widget_bitmap
    ( const std::vector<std::vector<bool>> bitmap
    , const size_t x
    , const size_t y
    ) : m_bitmap(bitmap)
      , m_x(x)
      , m_y(y)
{
}

widget_bitmap::~widget_bitmap() {}

void widget_bitmap::update() {} // bitmap is static

void widget_bitmap::draw(bitmap_image & img)
{
    std::cout << "widget_bitmap::draw()\n";
//    const uint8_t pixel_val {m_color_foreground}; // black

    // Display diamond in lower left
//    const std::vector<std::vector<int>> diamond =
//        {{0,0,0,0,1,0,0,0,0},
//         {0,0,0,1,1,1,0,0,0},
//         {0,0,1,1,1,1,1,0,0},
//         {0,1,1,1,1,1,1,1,0},
//         {1,1,1,1,1,1,1,1,1},
//         {0,1,1,1,1,1,1,1,0},
//         {0,0,1,1,1,1,1,0,0},
//         {0,0,0,1,1,1,0,0,0},
//         {0,0,0,0,1,0,0,0,0}};
//    const size_t diamond_width = diamond.at(0).size(); // assume all the same
//    const size_t diamond_height = diamond.size();

    if(m_bitmap.empty())
        return;
    if(m_bitmap.at(0).empty())
        return;

    const size_t bitmap_width = m_bitmap.at(0).size();
    for(int i = 0; i < m_bitmap.size(); ++i)
    {
        if(m_bitmap.at(i).empty())
            return;
    }
    const size_t bitmap_height = m_bitmap.size();

    for(size_t x = 0; x < bitmap_width; ++x)
    {
        for(size_t y = 0; y < bitmap_height; ++y)
        {
            const auto diamond_val = m_bitmap.at(y).at(x);

            const size_t pixel_x = x + m_x;
//            const size_t pixel_y = img.image_height_pixels() - bitmap_height + y;
            const size_t pixel_y = y + m_y;

            if(diamond_val)
            {
                img.set(pixel_x, pixel_y, m_color_foreground);
            }
        }
    }
}

size_t widget_bitmap::x() const { return m_x; }
size_t widget_bitmap::y() const { return m_y; }
size_t & widget_bitmap::x() { return m_x; }
size_t & widget_bitmap::y() { return m_y; }

uint8_t widget_bitmap::color_foreground() const { return m_color_foreground; }
uint8_t & widget_bitmap::color_foreground() { return m_color_foreground; }

uint8_t widget_bitmap::color_background() const { return m_color_background; }
uint8_t & widget_bitmap::color_background() { return m_color_background; }

}
