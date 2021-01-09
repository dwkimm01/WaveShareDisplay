//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_SCREEN_MANAGER_H
#define WSEINK_CPP_SCREEN_MANAGER_H

#include <map>
#include "i_screen_manager.h"

class screen_manager : public i_screen_mananger
{
public:
    screen_manager();

    virtual ~screen_manager();

    bool add_screen
        ( const std::string & screen_name
        , std::shared_ptr<i_screen> screen_ptr
        ) override;

    bool rem_screen
        ( const std::string & screen_name
        , std::shared_ptr<i_screen> & screen_ptr
        ) override;

    bool set_screen
        ( const std::string & screen_name
        ) override;

private:
    std::map<std::string, std::shared_ptr<i_screen>> m_screen_map;
};


#endif //WSEINK_CPP_SCREEN_MANAGER_H
