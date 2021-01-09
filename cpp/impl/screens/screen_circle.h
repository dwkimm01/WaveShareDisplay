//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_SCREEN_CIRCLE_H
#define WSEINK_CPP_SCREEN_CIRCLE_H

#include "interfaces/i_screen.h"

namespace waveshare_eink_cpp
{
class screen_circle : public i_screen
{
public:
    screen_circle();

    virtual ~screen_circle();

    virtual void draw(bitmap_image & img) override;
};

}
#endif //WSEINK_CPP_SCREEN_CIRCLE_H
