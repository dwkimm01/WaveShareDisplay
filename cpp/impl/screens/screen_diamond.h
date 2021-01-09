//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_SCREEN_DIAMOND_H
#define WSEINK_CPP_SCREEN_DIAMOND_H

#include "interfaces/i_screen.h"

namespace waveshare_eink_cpp
{
class screen_diamond : public i_screen
{
public:
    screen_diamond();

    virtual ~screen_diamond();

    virtual void draw(bitmap_image & img) override;
};

}
#endif //WSEINK_CPP_SCREEN_DIAMOND_H
