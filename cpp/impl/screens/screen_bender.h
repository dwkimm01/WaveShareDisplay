//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_SCREEN_BENDER_H
#define WSEINK_CPP_SCREEN_BENDER_H

#include "interfaces/i_screen.h"

namespace waveshare_eink_cpp
{
class screen_bender : public i_screen
{
public:
    screen_bender();

    virtual ~screen_bender();

    virtual void draw(bitmap_image & img) override;
};

}
#endif //WSEINK_CPP_SCREEN_BENDER_H
