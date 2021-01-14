//
// Created by Dave on 1/14/21.
//

#include <iostream>
#include "screen_currently_playing.h"


namespace waveshare_eink_cpp
{

screen_currently_playing::screen_currently_playing
    ( std::shared_ptr<lms_client> lms_client
    ) : m_lms_client(lms_client)
      , m_widget_currently_playing(new widget_string("Unknown", 10, 10))
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

                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
    m_widget_currently_playing->draw(img);
}

}