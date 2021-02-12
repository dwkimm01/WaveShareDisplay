//
// Created by Kimmel, David on 12/2/20.
//

#include <signal.h>
#include <iostream>
#include <chrono>

#include "bitmap_display_2in9.h"
#include "bitmap_display_2in9_null.h"
#include "active_timer.h"

#include "web_service/waveshare_web_service.h"
#include "web_service/lms_client.h"
#include "web_service/web_service.h"

#include "impl/screen_manager.h"
#include "impl/screens/screen_bender.h"
#include "impl/screens/screen_circle.h"
#include "impl/screens/screen_currently_playing.h"
#include "impl/screens/screen_diamond.h"
#include "impl/screens/screen_square.h"
#include "impl/screens/screen_x.h"


int main(int argc, char* argv[])
{
    using namespace std;
    using namespace waveshare_eink_cpp;
    cout << "Starting...\n";

    std::string host_url = "http://jmb:9000";
    std::string player_name = "jmba";

    if(argc < 3)
    {
        cout << "usage: host_url player_name\n";
        cout << " e.g.: " << host_url << " " << player_name;
        cout << endl;
        return 2;
    }
    else
    {
        host_url = argv[1];
        player_name = argv[2];
    }

    cout << "host_url [" << host_url << "]" << endl;
    cout << "player_name [" << player_name << "]" << endl;

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
    std::shared_ptr<lms_client> lms_client
        = std::make_shared<waveshare_eink_cpp::lms_client>
            ( host_url
            , player_name
            );

    screen_manager_ptr->add_screen("currently_playing", std::shared_ptr<i_screen>(new screen_currently_playing(lms_client)));
    screen_manager_ptr->set_screen("currently_playing");

    active_timer timer
        ( std::chrono::milliseconds(10000)
        , [screen_manager_ptr]()
            {
//                screen_manager_ptr->clear_current_screen(255);
                screen_manager_ptr->draw_current_screen();
                screen_manager_ptr->send_to_display();
            }
        );

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
