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
#include "bitmap_display_2in9_null.h"
#include "drawing.h"
#include "../c/lib/Fonts/fonts.h"
#include "waveshare_web_service.h"

#include "impl/screen_manager.h"
#include "impl/screens/screen_circle.h"
#include "impl/screens/screen_square.h"

void display_test()
{
    using namespace std;
    using namespace waveshare_eink_cpp;


    // Exception handling:ctrl + c
    signal(SIGINT, bitmap_display_2in9::exit_handler);

    std::shared_ptr<i_bitmap_display> display = std::make_shared<bitmap_display_2in9>();

    auto b = display->create_image();

    //const size_t m = std::min(b.image_width_pixels(), b.image_height_pixels());
    //for(int i = 0; i < m; ++i)
    //   b.set(i, i, 1);


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

    // Text
    drawing::Paint_DrawString_EN
            (b, 0, 0, "Hello"
                    , &Font16, drawing::d_WHITE
                    , drawing::d_BLACK
            );


    // Number
    drawing::Paint_DrawNum // TODO, doesn't seem to be displaying?
            (b
                    , 120, 10
                    , 187, &Font16
                    , drawing::d_WHITE
                    , drawing::d_BLACK
            );


    // Time
    const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    const time_t tt = std::chrono::system_clock::to_time_t(now);
    // const tm utc_tm = *gmtime(&tt);
    const tm local_tm = *localtime(&tt);

    drawing::paint_time_t pTime;
    pTime.Year = local_tm.tm_year + 1970;
    pTime.Month = local_tm.tm_mon + 1;
    pTime.Day = local_tm.tm_mday;
    pTime.Hour = local_tm.tm_hour;
    pTime.Min = local_tm.tm_min;
    pTime.Sec = local_tm.tm_sec;
    try
    {
        drawing::Paint_DrawTime(b, 30, 105, &pTime, &Font8, drawing::d_WHITE, drawing::d_BLACK);
    }
    catch(const std::exception &e)
    {
        std::cout << "Exception drawing time: " << e.what() << std::endl;
    }
    // Line
    drawing::Paint_DrawLine
            ( b
                    , 20, 20
                    , 40, 40
                    , drawing::d_WHITE, drawing::d_DOT_PIXEL_2X2
                    , drawing::d_LINE_STYLE_SOLID);

    // Rectangle
    drawing::Paint_DrawRectangle
            ( b
                    , 80, 80
                    , 100, 100
                    , drawing::d_WHITE
                    , drawing::d_DOT_PIXEL_4X4
                    , drawing::d_DRAW_FILL_EMPTY
            );

    // Circle
    drawing::Paint_DrawCircle
            (b
                    , 120, 80
                    , 20
                    , drawing::d_WHITE
                    , drawing::d_DOT_PIXEL_4X4
                    , drawing::d_DRAW_FILL_EMPTY
            );

    display->display(b);


//    // Cube vertices
//    const std::vector<std::tuple<double, double, double>> cube_vertices
//        { {1,1,1}
//        , {1,1,-1}
//        , {1,-1,-1}
//        , {1,-1,1}
//        , {-1,1,1}
//        , {-1,1,-1}
//        , {-1,-1,-1}
//        , {-1,-1,1}
//        };
//
//    Matrix cube_vertices
//
//    // Cube edges
//    std::vector<std::tuple<size_t, size_t>> cube_edges
//        { {0,1},  {1,5},  {5,4},  {4,0}  // edges of the top face
//        , {7,3},  {3,2},  {2,6},  {6,7}  // edges of the bottom face
//        , {1,2},  {0,3},  {4,7},  {5,6}  // edges connecting top face to bottom face
//        };

    std::this_thread::sleep_for(chrono::milliseconds(10000) );
}

int main(int argc, char* argv[])
{
    using namespace std;
    using namespace waveshare_eink_cpp;
    cout << "Starting...\n";

    // Exception handling:ctrl + c
    signal(SIGINT, bitmap_display_2in9::exit_handler);
    // Bitmap display
    std::shared_ptr<i_bitmap_display> bitmap_display;
    try
    {
        bitmap_display = std::make_shared<bitmap_display_2in9>();
    }
    catch(const std::exception & e)
    {
        std::cout << "Exception creating display, using null display\n";
        bitmap_display = std::make_shared<bitmap_display_2in9_null>();
    }
    // Screen manager
    std::shared_ptr<i_screen_mananger> screen_manager_ptr = std::make_shared<screen_manager>(bitmap_display);

    // Screens
    screen_manager_ptr->add_screen("circle", std::shared_ptr<i_screen>(new screen_circle()));
    screen_manager_ptr->add_screen("square", std::shared_ptr<i_screen>(new screen_square()));


#ifdef ENABLE_DROGON
    waveshare_web_service s(screen_manager_ptr);
#else
    display_test();
#endif

    cout << "Done." << endl;
    return 0;
}
