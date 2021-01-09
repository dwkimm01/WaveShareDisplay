//
// Created by Dave on 1/6/21.
//

#ifndef WSEINK_CPP_I_SCREEN_MANAGER_H
#define WSEINK_CPP_I_SCREEN_MANAGER_H

#include <string>
#include <memory>
#include "i_screen.h"

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
};

#endif //WSEINK_CPP_I_DISPLAY_MANAGER_H
