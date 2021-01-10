//
// Created by Dave on 1/10/21.
//

#ifndef WSEINK_CPP_SCREEN_WIDGETS_H
#define WSEINK_CPP_SCREEN_WIDGETS_H

#include <vector>
#include <memory>
#include "interfaces/i_screen_manager.h"
#include "interfaces/i_widget.h"

namespace waveshare_eink_cpp
{

class screen_widgets : public i_screen
{
public:
    screen_widgets();
    screen_widgets(std::shared_ptr<i_widget> widget);
    screen_widgets(std::vector<std::shared_ptr<i_widget>> & widgets);

    virtual ~screen_widgets();

    void draw(bitmap_image & img) override;

private:
    std::vector<std::shared_ptr<i_widget>> m_widgets;
};
}

#endif //WSEINK_CPP_SCREEN_WIDGETS_H
