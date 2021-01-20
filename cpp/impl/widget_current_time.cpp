//
// Created by Dave on 1/19/21.
//
#include <iostream>
#include <chrono>
#include "drawing.h"
#include "widget_current_time.h"


namespace waveshare_eink_cpp
{

widget_current_time::widget_current_time() {}
widget_current_time::widget_current_time
    ( const size_t x
    , const size_t y
    , const uint8_t color_foreground
    , const uint8_t color_background
    ) : m_x(x)
      , m_y(y)
      , m_color_foreground(color_foreground)
      , m_color_background(color_background)
{}

widget_current_time::~widget_current_time() {}

void widget_current_time::update() {}

void widget_current_time::draw(bitmap_image & img)
{
    std::cout << "drawing current time" << std::endl;
    // Draw time
    const time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//        tm utc_tm = *gmtime(&tt);
    std::cout << "converting current time to local time" << std::endl;
    tm local_tm = *localtime(&tt);



    drawing::paint_time_t paint_time;
    paint_time.Hour = local_tm.tm_hour;
    paint_time.Min = local_tm.tm_min;
    paint_time.Sec = 0;
    drawing::Paint_DrawTime
            ( img
            , m_x
            , m_y
            , &paint_time
            , &Font12
            , (drawing::color_t) m_color_foreground
            , (drawing::color_t) m_color_background
            );
}

size_t widget_current_time::x() const { return m_x; }
size_t widget_current_time::y() const { return m_y; }

size_t & widget_current_time::x() { return m_x; }
size_t & widget_current_time::y() { return m_y; }

uint8_t widget_current_time::color_foreground() const { return m_color_foreground; }
uint8_t & widget_current_time::color_foreground() { return m_color_foreground; }

uint8_t widget_current_time::color_background() const { return m_color_background; }
uint8_t & widget_current_time::color_background() { return m_color_background; }

}
