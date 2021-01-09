//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_BITMAP_DISPLAY_2IN9_NULL_H
#define WSEINK_CPP_BITMAP_DISPLAY_2IN9_NULL_H

#include "interfaces/i_bitmap_display.h"

namespace waveshare_eink_cpp
{

// Pretend to have a 2in9 display
class bitmap_display_2in9_null : public i_bitmap_display
{
public:

    bitmap_display_2in9_null();
    virtual ~bitmap_display_2in9_null();

    // Info
    size_t width_pixels() const override;
    size_t height_pixels() const override;

    // Actions
    void clear() override;
    void sleep() override;
    void display(const bitmap_image & b) override;

    // Image creation
    bitmap_image create_image() override;


};
}

#endif //WSEINK_CPP_BITMAP_DISPLAY_2IN9_NULL_H
