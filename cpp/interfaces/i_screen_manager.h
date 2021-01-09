//
// Created by Dave on 1/6/21.
//

#ifndef WSEINK_CPP_I_SCREEN_MANAGER_H
#define WSEINK_CPP_I_SCREEN_MANAGER_H

#include <string>
#include <memory>
#include "i_screen.h"
#include "bitmap_image.h"

namespace waveshare_eink_cpp
{
class i_screen_mananger
{
public:
    virtual ~i_screen_mananger() {}

    virtual bool add_screen
        ( const std::string & screen_name
        , std::shared_ptr<i_screen> screen_ptr
        ) = 0;

    virtual bool rem_screen
        ( const std::string & screen_name
        , std::shared_ptr<i_screen> & screen_ptr
        ) = 0;

    virtual bool set_screen
        ( const std::string & screen_name
        ) = 0;

    virtual bool draw_current_screen
        (
        ) = 0;

    virtual bool clear_current_screen
        ( const uint8_t val
        ) = 0;

    virtual std::vector<std::string> list_screens
        (
        ) = 0;
};
}
#endif //WSEINK_CPP_I_DISPLAY_MANAGER_H
