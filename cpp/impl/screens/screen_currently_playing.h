//
// Created by Dave on 1/14/21.
//

#ifndef WSEINK_CPP_SCREEN_CURRENTLY_PLAYING_H
#define WSEINK_CPP_SCREEN_CURRENTLY_PLAYING_H

#include <memory>
#include <thread>
#include <mutex>
#include "interfaces/i_screen.h"
#include "impl/widget_string.h"
#include "web_service/lms_client.h"

namespace waveshare_eink_cpp
{

class screen_currently_playing : public i_screen
{
public:
    screen_currently_playing
        ( std::shared_ptr<lms_client> lms_client
        );

    virtual ~screen_currently_playing();

    void draw(bitmap_image & img) override;

private:
    std::shared_ptr<lms_client> m_lms_client;
    std::unique_ptr<widget_string> m_widget_currently_playing;

    std::mutex m_mutex;
    bool m_running {false};
    std::thread m_thread;
};

}

#endif //WSEINK_CPP_SCREEN_CURRENTLY_PLAYING_H
