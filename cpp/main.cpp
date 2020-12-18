//
// Created by Kimmel, David on 12/2/20.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "bitmap_display_2in9.h"

int main(int argc, char* argv[])
{
    using namespace std;
    using namespace waveshare_eink_cpp;

    cout << "Starting...\n";

    std::shared_ptr<i_bitmap_display> display = std::make_shared<waveshare_eink_cpp::bitmap_display_2in9>();

    auto b = display->create_image();

    //const size_t m = std::min(b.image_width_pixels(), b.image_height_pixels());
    //for(int i = 0; i < m; ++i)
    //   b.set(i, i, 1);

    for(size_t x = b.image_width_pixels()-10; x < b.image_width_pixels(); ++x)
    {
       for(size_t y = b.image_height_pixels()-10; y < b.image_height_pixels(); ++y)
       {
          b.set(x, y, 1);
       }
    }

/*
    for(int x = 0; x < b.image_width_pixels(); ++x)
    {
        for(int y = 0; y < b.image_height_pixels(); ++y)
        {
           if(x > 0)
              b.set(x, y, 1);
//            if(0 == ((y * b.image_width_pixels() + x) % 2))
//                b.set(x, y, 1);
        }
    }
*/

    display->display(b);

    std::this_thread::sleep_for(chrono::milliseconds(10000) );

    cout << "Done." << endl;
    return 0;
}
