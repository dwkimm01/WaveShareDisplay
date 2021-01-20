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
      , m_widget_currently_playing(new widget_string("Unknown", 10, 20, 255, 0))
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
                    const std::string currently_playing_full_str = m_lms_client->currently_playing();
                    // Limit string to a certain length
                    std::string currently_playing;

                    const size_t max_chars_total {20};
                    currently_playing.reserve(max_chars_total);
                    for(int i = 0; i < max_chars_total; ++i)
                    {
                        currently_playing.push_back(currently_playing_full_str.at(i));
                    }

                    // If length exceeded overwrite end with ...
                    if(currently_playing_full_str.size() > max_chars_total)
                    {
                        for(int i = (max_chars_total - 1) - 3; i < max_chars_total; ++i)
                        {
                            currently_playing.at(i) = '.';
                        }
                    }


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

    // White background
    img.fill(bitmap_image::CWHITE);
    m_widget_currently_playing->draw(img);

    {
        // Draw time block
        
        const std::vector<int> x_vals_vec 
            { 101, 100, 50, 50, 50, 50, 50, 50, 50, 50
            , 49, 48, 47, 46, 45, 44, 43, 42, 41, 40
            };
        
        const int time_block_height {20};
        // const int time_block_width {70};

        for(int i = 0; i < time_block_height; ++i)
        {
            int time_block_width = 70;
            if(x_vals_vec.size() > i)
                time_block_width = x_vals_vec[i];

            drawing::Paint_DrawLine
                ( img
                , img.image_width_pixels() - time_block_width, img.image_height_pixels() - i
                , img.image_width_pixels() - 0, img.image_height_pixels() - i
                , drawing::d_BLACK
                , drawing::d_DOT_PIXEL_DFT
                , drawing::d_LINE_STYLE_SOLID
                );
        }

        // Move clock to correct position
        m_widget_current_time->x() = img.image_width_pixels() - 40;
        m_widget_current_time->y() = img.image_height_pixels() - 15;
        m_widget_current_time->draw(img);
    }

}

}