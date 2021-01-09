//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_SCREEN_X_H
#define WSEINK_CPP_SCREEN_X_H

#include "interfaces/i_screen.h"

namespace waveshare_eink_cpp
{
class screen_x : public i_screen
{
public:
    screen_x();

    virtual ~screen_x();

    virtual void draw(bitmap_image & img) override;
};

}
#endif //WSEINK_CPP_SCREEN_X_H
