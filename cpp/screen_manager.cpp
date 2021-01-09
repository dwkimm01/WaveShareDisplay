//
// Created by Dave on 1/9/21.
//

#include "screen_manager.h"


bool screen_manager::add_screen
    ( const std::string & screen_name
    , std::shared_ptr<i_screen> screen_ptr
    )
{
    auto res = m_screen_map.emplace(std::make_pair(screen_name, screen_ptr));
    return std::get<1>(res);
}

bool screen_manager::rem_screen
    ( const std::string & screen_name
    , std::shared_ptr<i_screen> & screen_ptr
    )
{
    auto itr = m_screen_map.find(screen_name);
    if(itr == m_screen_map.end())
        return false;
    screen_ptr = itr->second;
    m_screen_map.erase(itr);
    return true;
}

bool screen_manager::set_screen
    ( const std::string & screen_name
    )
{
    auto itr = m_screen_map.find(screen_name);
    if(itr == m_screen_map.end())
        return false;
    itr->second->update_screen();
    return true;
}

