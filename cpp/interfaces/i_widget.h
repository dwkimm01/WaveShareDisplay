//
// Created by Dave on 1/10/21.
//

#ifndef WSEINK_CPP_I_WIDGET_H
#define WSEINK_CPP_I_WIDGET_H

#include "bitmap_image.h"

namespace waveshare_eink_cpp
{

class i_widget
{
public:
    virtual ~i_widget() {}

    virtual void update() = 0;

    virtual void draw(bitmap_image & img) = 0;

    virtual size_t x() const = 0;
    virtual size_t y() const = 0;

    virtual size_t & x() = 0;
    virtual size_t & y() = 0;

    virtual uint8_t color_foreground() const = 0;
    virtual uint8_t & color_foreground() = 0;

    virtual uint8_t color_background() const = 0;
    virtual uint8_t & color_background() = 0;

};

}

#endif //WSEINK_CPP_I_WIDGET_H
