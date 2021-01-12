//
// Created by Dave on 1/11/21.
//

#ifndef WSEINK_CPP_WIDGET_STRING_H
#define WSEINK_CPP_WIDGET_STRING_H

#include <string>
#include "interfaces/i_widget.h"

namespace waveshare_eink_cpp
{

class widget_string : public i_widget
{
public:
    widget_string();
    widget_string
        ( const std::string & text
        , const size_t x
        , const size_t y
        );
    virtual ~widget_string();

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

    std::string & text();
    const std::string & text() const;

private:
    size_t m_x {0};
    size_t m_y {0};

    uint8_t m_color_foreground {0};
    uint8_t m_color_background {0};

    std::string m_text;
};
}

#endif //WSEINK_CPP_WIDGET_STRING_H
