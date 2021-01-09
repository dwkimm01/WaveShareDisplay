//
// Created by Kimmel, David on 12/2/20.
//

#ifndef E_PAPER_BITMAP_DISPLAY_2IN9_H
#define E_PAPER_BITMAP_DISPLAY_2IN9_H

#include "interfaces/i_bitmap_display.h"

namespace waveshare_eink_cpp
{

class bitmap_display_2in9 : public i_bitmap_display
{
public:
    static void exit_handler(int signo);

    bitmap_display_2in9();
    virtual ~bitmap_display_2in9();

    // Info
    size_t width_pixels() const override;
    size_t height_pixels() const override;

    // Actions
    void clear() override;
    void sleep() override;
    void display(const bitmap_image & b) override;

    // Image creation
    bitmap_image create_image() override;

private:
    void display_init(bool full);
    void display_sleep();
};

}


#endif //E_PAPER_BITMAP_DISPLAY_2IN9_H
