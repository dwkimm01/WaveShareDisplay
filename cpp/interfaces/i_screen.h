//
// Created by Dave on 1/6/21.
//

#ifndef WSEINK_CPP_I_SCREEN_H
#define WSEINK_CPP_I_SCREEN_H

#include "bitmap_image.h"

namespace waveshare_eink_cpp
{

class i_screen
{
public:
    virtual ~i_screen() {}

    virtual void draw(bitmap_image & img) = 0;
};

}
#endif //WSEINK_CPP_I_SCREEN_H
