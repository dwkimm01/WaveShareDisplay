//
// Created by Dave on 1/10/21.
//

#include "screen_widgets.h"

namespace waveshare_eink_cpp
{

screen_widgets::screen_widgets() {}
screen_widgets::screen_widgets(std::shared_ptr<i_widget> widget)
{
    m_widgets.push_back(widget);
}

screen_widgets::screen_widgets(std::vector<std::shared_ptr<i_widget>> & widgets)
    : m_widgets(widgets)
{}

screen_widgets::~screen_widgets() {}

void screen_widgets::draw(bitmap_image & img)
{
    for(auto & widget : m_widgets)
    {
        widget->draw(img);
    }
}

}
