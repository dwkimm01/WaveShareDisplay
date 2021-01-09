//
// Created by Kimmel, David on 12/1/20.
//

#ifndef E_PAPER_IBITMAPDISPLAY_H
#define E_PAPER_IBITMAPDISPLAY_H

#include "../bitmap_image.h"

namespace waveshare_eink_cpp
{

class i_bitmap_display
{
public:
    virtual ~i_bitmap_display() {}

    // Info
    virtual size_t width_pixels() const = 0;
    virtual size_t height_pixels() const = 0;

    // Actions
    virtual void clear() = 0;
    virtual void sleep() = 0;
    virtual void display(const bitmap_image &) = 0;

    // Image creation
    virtual bitmap_image create_image() = 0;
};

}
#endif //E_PAPER_IBITMAPDISPLAY_H
