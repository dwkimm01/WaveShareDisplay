//
// Created by Dave on 1/10/21.
//

#ifndef WSEINK_CPP_WIDGET_BITMAP_H
#define WSEINK_CPP_WIDGET_BITMAP_H

#include <vector>
#include "interfaces/i_widget.h"

namespace waveshare_eink_cpp
{
    
class widget_bitmap : public i_widget 
{
public:
    widget_bitmap();
    widget_bitmap
        ( const std::vector<std::vector<bool>> bitmap
        , const size_t x
        , const size_t y
        );
    virtual ~widget_bitmap();

    void update() override;

    void draw(bitmap_image & img) override;

    size_t x() const override;
    size_t y() const override;

    size_t & x() override;
    size_t & y() override;

    uint8_t color_foreground() const override;
    uint8_t & color_foreground() override;

    uint8_t color_background() const override;
    uint8_t & color_background() override;

private:
    size_t m_x {0};
    size_t m_y {0};

    uint8_t m_color_foreground {0};
    uint8_t m_color_background {0};

    std::vector<std::vector<bool>> m_bitmap;
};
}

#endif //WSEINK_CPP_WIDGET_BITMAP_H
