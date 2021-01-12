//
// Created by Dave on 1/11/21.
//

#include "widget_string.h"
#include "drawing.h"

namespace waveshare_eink_cpp
{

widget_string::widget_string() {}
widget_string::widget_string
    ( const std::string & text
    , const size_t x
    , const size_t y
    ) : m_x(x)
      , m_y(y)
      , m_text(text)
{}

widget_string::~widget_string() {}

void widget_string::update() {}

void widget_string::draw(bitmap_image & img)
{
    drawing::Paint_DrawString_EN
            (img, m_x, m_y, m_text.c_str()
                    , &Font16, drawing::d_WHITE
                    , drawing::d_BLACK
            );
}

size_t widget_string::x() const { return m_x; }
size_t widget_string::y() const { return m_y; }

size_t & widget_string::x() { return m_x; }
size_t & widget_string::y() { return m_y; }

uint8_t widget_string::color_foreground() const { return m_color_foreground; }
uint8_t & widget_string::color_foreground() { return m_color_foreground; }

uint8_t widget_string::color_background() const { return m_color_background; }
uint8_t & widget_string::color_background() { return m_color_background; }

std::string & widget_string::text() { return m_text; }
const std::string & widget_string::text() const { return m_text; }

}