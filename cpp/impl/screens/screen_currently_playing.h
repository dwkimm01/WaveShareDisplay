//
// Created by Dave on 1/14/21.
//

#ifndef WSEINK_CPP_SCREEN_CURRENTLY_PLAYING_H
#define WSEINK_CPP_SCREEN_CURRENTLY_PLAYING_H

#include <memory>
#include "interfaces/i_screen.h"
#include "impl/widget_string.h"

namespace waveshare_eink_cpp
{

class screen_currently_playing : public i_screen
{
public:
    screen_currently_playing();

    virtual ~screen_currently_playing();

    void draw(bitmap_image & img) override;

private:
    std::unique_ptr<widget_string> m_widget_currently_playing;
};

}

#endif //WSEINK_CPP_SCREEN_CURRENTLY_PLAYING_H
