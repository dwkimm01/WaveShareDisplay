//
// Created by Dave on 1/14/21.
//

#include "screen_currently_playing.h"


namespace waveshare_eink_cpp
{

screen_currently_playing::screen_currently_playing()
    : m_widget_currently_playing(new widget_string("Unknown", 10, 10))
{}

screen_currently_playing::~screen_currently_playing()
{}

void screen_currently_playing::draw(bitmap_image & img)
{
    m_widget_currently_playing->draw(img);
}

}