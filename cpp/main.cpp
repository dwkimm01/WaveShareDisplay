//
// Created by Kimmel, David on 12/2/20.
//

#include <iostream>
#include <thread>
#include <chrono>

#include <signal.h>


#include "bitmap_display_2in9.h"
#include "bitmap_display_2in9_null.h"
#include "drawing.h"
#include "../c/lib/Fonts/fonts.h"
#include "web_service/waveshare_web_service.h"
#include "web_service/lms_client.h"
#include "web_service/web_service.h"

#include "impl/screen_manager.h"
#include "impl/screens/screen_bender.h"
#include "impl/screens/screen_circle.h"
#include "impl/screens/screen_currently_playing.h"
#include "impl/screens/screen_diamond.h"
#include "impl/screens/screen_square.h"
#include "impl/screens/screen_widgets.h"
#include "impl/screens/screen_x.h"

#include "impl/bitmaps.h"
#include "impl/widget_bitmap.h"
#include "impl/widget_string.h"

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
    screen_manager_ptr->add_screen("diamond", std::shared_ptr<i_screen>(new screen_diamond()));
    screen_manager_ptr->add_screen("square", std::shared_ptr<i_screen>(new screen_square()));
    screen_manager_ptr->add_screen("x", std::shared_ptr<i_screen>(new screen_x()));
    screen_manager_ptr->add_screen("bender", std::shared_ptr<i_screen>(new screen_bender()));

    /*
//TODO - fix bender teeth - displayed wrong now
//TODO - why isn't the play button showing under Judah's name?
    bitmaps bmp;
    auto widget_bmp_ptr = std::shared_ptr<widget_bitmap>(new widget_bitmap(bmp.get("play"), 0, 20));
    auto widget_string_ptr = std::shared_ptr<widget_string>(new widget_string("Judah", 0, 0));
    std::vector<std::shared_ptr<i_widget>> widget_vec { widget_bmp_ptr, widget_string_ptr};
    auto screen_widgets_ptr = std::make_shared<screen_widgets>(widget_vec);

    screen_manager_ptr->add_screen("widgets", std::shared_ptr<i_screen>(screen_widgets_ptr));
*/

#ifdef ENABLE_DROGON

    // Add server endpoints
    waveshare_web_service s(screen_manager_ptr);
    std::shared_ptr<lms_client> lms_client;

    screen_manager_ptr->add_screen("currently_playing", std::shared_ptr<i_screen>(new screen_currently_playing(lms_client)));


    // Run this first to get background threads running
    web_service ws;
    ws.run_in_background();


//    client.play();
//    client.pause();
//    const string currently_playing_title = lms_client->currently_playing();
//    cout << "Currently Playing Title: " << currently_playing_title << endl;

    cout << "waiting for shutdown cmd" << endl;

    ws.join();
#endif
    cout << "Done, exiting." << endl;
    return 0;
}
