//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_SCREEN_SQUARE_H
#define WSEINK_CPP_SCREEN_SQUARE_H

#include "interfaces/i_screen.h"

namespace waveshare_eink_cpp
{
class screen_square : public i_screen
{
public:
    screen_square();

    virtual ~screen_square();

    virtual void draw(bitmap_image & img) override;
};

}
#endif //WSEINK_CPP_SCREEN_SQUARE_H
