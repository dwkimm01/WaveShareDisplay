//
// Created by Dave on 1/14/21.
//

#include <iostream>
#include "screen_currently_playing.h"
#include "drawing.h"

namespace waveshare_eink_cpp
{

screen_currently_playing::screen_currently_playing
    ( std::shared_ptr<lms_client> lms_client
    ) : m_lms_client(lms_client)
      , m_widget_currently_playing(new widget_string("Unknown", 10, 20, 0, 255))
      , m_widget_current_time(new widget_current_time(0, 0, 0, 255))
{
    m_running = true;
    m_thread = std::thread([&]()
        {
            while(m_running)
            {

                try
                {
                    // Get updated currently playing
                    const std::string currently_playing = m_lms_client->currently_playing();

                    {
                        // Update
                        std::lock_guard<std::mutex> lock(m_mutex);
                        m_widget_currently_playing->text() = currently_playing;
                    }

                }
                catch(const std::exception &e)
                {
                    std::cout << "Exception updating currently playing: " << e.what() << std::endl;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            }

        });
}

screen_currently_playing::~screen_currently_playing()
{
    m_running = false;
    if(m_thread.joinable())
    {
        m_thread.join();
    }
}

void screen_currently_playing::draw(bitmap_image & img)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << "screen currently playing drawing \"" << m_widget_currently_playing->text() << "\"" << std::endl;
    m_widget_currently_playing->draw(img);

    {
        // Draw time block
//        const int time_block_height {40};
//        const int time_block_width {80};
//
//        for(int i = 0; i < time_block_height; ++i)
//        {
//            drawing::Paint_DrawLine
//                ( img
//                , img.image_width_pixels() - time_block_width, img.image_height_pixels() - i
//                , img.image_width_pixels() - 0, img.image_height_pixels() - i
//                , drawing::d_BLACK
//                , drawing::d_DOT_PIXEL_DFT
//                , drawing::d_LINE_STYLE_SOLID
//                );
//        }

        // Move clock to correct position
        m_widget_current_time->x() = img.image_width_pixels() - 50;
        m_widget_current_time->y() = img.image_height_pixels() - 20;
        m_widget_current_time->draw(img);
    }

}

}