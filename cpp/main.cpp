//
// Created by Kimmel, David on 12/2/20.
//

#include <iostream>
#include <thread>
#include <chrono>

#include <signal.h>
#include <cmath>
#include <math.h>

#include "bitmap_display_2in9.h"


int main(int argc, char* argv[])
{
    using namespace std;
    using namespace waveshare_eink_cpp;

    cout << "Starting...\n";

    // Exception handling:ctrl + c
    signal(SIGINT, bitmap_display_2in9::exit_handler);

    std::shared_ptr<i_bitmap_display> display = std::make_shared<bitmap_display_2in9>();

    auto b = display->create_image();

    //const size_t m = std::min(b.image_width_pixels(), b.image_height_pixels());
    //for(int i = 0; i < m; ++i)
    //   b.set(i, i, 1);

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
                b.set(x, y, 1);
            }
        }
    }

    // Display box in lower right
    for(size_t x = b.image_width_pixels()-10; x < b.image_width_pixels(); ++x)
    {
       for(size_t y = b.image_height_pixels()-10; y < b.image_height_pixels(); ++y)
       {
          b.set(x, y, 1);
       }
    }

    {
        // Display diamond in lower left
        std::vector<std::vector<int>> diamond =
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
                const size_t pixel_y = b.image_height_pixels() - diamond_height + y;
    
                if(0 != diamond_val)
                    b.set(pixel_x, pixel_y, 1);
            }
        }
    }


    {
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

                const size_t pixel_x = b.image_width_pixels() - x_width + x;
                const size_t pixel_y = b.image_height_pixels() - x_height + y;

                if(0 != xxx_val)
                    b.set(pixel_x, pixel_y, 1);
            }
        }
    }
    
    // Display...
    // - checkerboard pattern
    // - gradient pattern
    // - cool info

    display->display(b);

    std::this_thread::sleep_for(chrono::milliseconds(10000) );

    cout << "Done." << endl;
    return 0;
}
