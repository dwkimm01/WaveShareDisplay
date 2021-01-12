//
// Created by Kimmel, David on 12/2/20.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <signal.h>
#include "bitmap_display_2in9.h"

extern "C" {


// ----------------------------------------
//#include "GUI_Paint.h"
//#include "GUI_BMPfile.h"
#include "../c/examples/ImageData.h" // TODO, fix relative path
#include "Debug.h"
#include <stdlib.h> // malloc() free()
// ----------------------------------------

#include "../c/lib/Config/DEV_Config.h"
#include "../c/lib/e-Paper/EPD_2in9.h"
}

namespace waveshare_eink_cpp
{
void bitmap_display_2in9::exit_handler(int signo)
{
    // System Exit
    std::cout << "Exit handler: calling dev module exit" << std::endl;
    DEV_Module_Exit();
    exit(0);
}

bitmap_display_2in9::bitmap_display_2in9()
{
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
    return EPD_2IN9_WIDTH;
}

size_t bitmap_display_2in9::height_pixels() const
{
    return EPD_2IN9_HEIGHT;
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
    EPD_2IN9_Display(const_cast<unsigned char*>(b.data()));
}

bitmap_image bitmap_display_2in9::create_image()
{
    bitmap_image b
        ( width_pixels()
        , height_pixels()
        , bitmap_image::MIRROR_VERTICAL
        , bitmap_image::ROT_90
//    , bitmap_image::MIRROR_NONE
//    , bitmap_image::ROT_0
        , bitmap_image::CWHITE
        );

    /**
     * MIRROR_HORIZONTAL + ROT_90
     * /------------\
     * |            | wires
     * |           +| wires
     * \------------/
     *
     * MIRROR_NONE + ROT_0 - but it's facing "down" instead of towards the middle of the screen
     * /------------\
     * |+           | wires
     * |            | wires
     * \------------/
     *
     * MIRROR_VERT + ROT_90 - Perfect for music robot (face) layout
     * /------------\
     * |+           | wires
     * |            | wires
     * \------------/

     */

    return b;
}


// ---------------------------------------------------------------------------
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
}

}
