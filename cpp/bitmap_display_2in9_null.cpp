//
// Created by Dave on 1/9/21.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "bitmap_display_2in9_null.h"

#include "../c/lib/Config/DEV_Config.h"
#include "../c/lib/e-Paper/EPD_2in9.h"

namespace waveshare_eink_cpp
{

bitmap_display_2in9_null::bitmap_display_2in9_null()
{
    std::cout << "bitmap_display_2in9_null::bitmap_display_2in9_null()\n";
}

bitmap_display_2in9_null::~bitmap_display_2in9_null()
{
    std::cout << "bitmap_display_2in9_null::~bitmap_display_2in9_null()\n";
}

size_t bitmap_display_2in9_null::width_pixels() const
{
    return EPD_2IN9_WIDTH;
}

size_t bitmap_display_2in9_null::height_pixels() const
{
    return EPD_2IN9_HEIGHT;
}

void bitmap_display_2in9_null::clear()
{
    std::cout << "bitmap_display_2in9_null::clear()\n";
    sleep();
}

void bitmap_display_2in9_null::sleep()
{
//    DEV_Delay_ms(500); // calls bcm2835_delay, or delay, or usleep in a loop
    std::this_thread::sleep_for(std::chrono::milliseconds(500) );
}

void bitmap_display_2in9_null::display(const bitmap_image & b)
{
    std::cout << "bitmap_display_2in9_null::display()\n";
}

bitmap_image bitmap_display_2in9_null::create_image()
{
    std::cout << "bitmap_display_2in9_null::create_image()\n";
    bitmap_image b
        ( width_pixels()
        , height_pixels()
        , bitmap_image::ROT_90
        , bitmap_image::CWHITE
        );
    return b;
}


}