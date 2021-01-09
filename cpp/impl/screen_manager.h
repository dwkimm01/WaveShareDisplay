//
// Created by Dave on 1/9/21.
//

#ifndef WSEINK_CPP_SCREEN_MANAGER_H
#define WSEINK_CPP_SCREEN_MANAGER_H

#include <map>
#include <mutex>
#include "interfaces/i_screen_manager.h"
#include "interfaces/i_bitmap_display.h"

namespace waveshare_eink_cpp
{

class screen_manager : public i_screen_mananger
{
public:
    screen_manager
        ( std::shared_ptr<i_bitmap_display> bitmap_display_ptr
        );

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

    bool draw_current_screen
        (
        ) override;

private:
    std::shared_ptr<i_bitmap_display> m_bitmap_display_ptr;
    bitmap_image m_img;

    std::mutex m_mutex;
    std::map<std::string, std::shared_ptr<i_screen>> m_screen_map;
    std::shared_ptr<i_screen> m_current_screen;
};
}

#endif //WSEINK_CPP_SCREEN_MANAGER_H
