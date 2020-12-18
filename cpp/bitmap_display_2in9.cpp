//
// Created by Kimmel, David on 12/2/20.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "bitmap_display_2in9.h"

// #define USE_WIRINGPI_LIB 1

extern "C" {
#include "../c/examples/EPD_Test.h"
#include "../c/lib/Config/DEV_Config.h"
#include "../c/lib/e-Paper/EPD_2in9.h"
}

namespace waveshare_eink_cpp
{

bitmap_display_2in9::bitmap_display_2in9()
{
//#ifdef USE_WIRINGPI_LIB
//  blah blah
//#endif

    // TODO, exit handler "DEV_Module_Exit()
    // ... signal(SIGINT, Handler);

    // Taken from EPD_2in9_test.c

    // Module Init
    const auto dev_module_init_result = DEV_Module_Init();
    if(dev_module_init_result != 0)
    {
        throw std::runtime_error("Could not initialize eink board " + std::to_string(dev_module_init_result));
    }

    std::cout << "dev_module_init_result = " << (int) dev_module_init_result << std::endl;

    // Display init
    display_init(true);
}

bitmap_display_2in9::~bitmap_display_2in9()
{
    // Clear display
    display_init(true);
    clear();
    // Put display to sleep
    EPD_2IN9_Sleep();
    // Module close
    DEV_Module_Exit();
}

size_t bitmap_display_2in9::width_pixels() const
{
    // EPD_2IN9_WIDTH       128
    return 128;
}

size_t bitmap_display_2in9::height_pixels() const
{
    // EPD_2IN9_HEIGHT      296
    return 296;
}

void bitmap_display_2in9::clear()
{
    EPD_2IN9_Clear();
    sleep();
}

void bitmap_display_2in9::sleep()
{
//    DEV_Delay_ms(500); // calls bcm2835_delay, or delay, or usleep in a loop
    std::this_thread::sleep_for(std::chrono::milliseconds(500) );
}

void bitmap_display_2in9::display(const bitmap_image & b)
{
//    EPD_2IN9_Display(UBYTE *Image)
    EPD_2IN9_Display(const_cast<unsigned char*>(b.data()));
}

bitmap_image bitmap_display_2in9::create_image()
{
    bitmap_image b
        ( width_pixels()
        , height_pixels()
        , bitmap_image::ROT_90
        , bitmap_image::CWHITE
        );
    return b;
}

void bitmap_display_2in9::display_init(bool full)
{
    if(full)
    {
        EPD_2IN9_Init(EPD_2IN9_FULL);
    }
    else
    {
        EPD_2IN9_Init(EPD_2IN9_PART);
    }
}

void bitmap_display_2in9::display_sleep()
{
    EPD_2IN9_Sleep();
/*
    EPD_2IN9_SendCommand(0x10);
    EPD_2IN9_SendData(0x01);
    // EPD_2IN9_ReadBusy();
*/
}



}