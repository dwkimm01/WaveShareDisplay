//
// Created by Dave on 1/9/21.
//

#include "screen_manager.h"

namespace waveshare_eink_cpp
{

screen_manager::screen_manager(std::shared_ptr<i_bitmap_display> bitmap_display_ptr)
    : m_bitmap_display_ptr(bitmap_display_ptr)
    , m_img(bitmap_display_ptr->create_image())
{
}

screen_manager::~screen_manager() {}

bool screen_manager::add_screen
    ( const std::string & screen_name
    , std::shared_ptr<i_screen> screen_ptr
    )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto res = m_screen_map.emplace(std::make_pair(screen_name, screen_ptr));
    return std::get<1>(res);
}

bool screen_manager::rem_screen
    ( const std::string & screen_name
    , std::shared_ptr<i_screen> & screen_ptr
    )
{
    std::lock_guard<std::mutex> lock(m_mutex);
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
    std::lock_guard<std::mutex> lock(m_mutex);
    auto itr = m_screen_map.find(screen_name);
    if(itr == m_screen_map.end())
        return false;
    m_current_screen = itr->second;
    return true;
}

bool screen_manager::draw_current_screen
    (
    )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_current_screen)
        return false;
    if(!m_bitmap_display_ptr)
        return false;

    // Clear first?
    m_current_screen->draw(m_img);
    m_bitmap_display_ptr->display(m_img);
    return true;
}

bool screen_manager::clear_current_screen
    ( const uint8_t val
    )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_bitmap_display_ptr)
        return false;

    m_img.fill(val);
    m_bitmap_display_ptr->display(m_img);
    return true;
}

std::vector<std::string> screen_manager::list_screens
    (
    )
{
    std::vector<std::string> screen_vec;

    std::lock_guard<std::mutex> lock(m_mutex);
    screen_vec.reserve(m_screen_map.size());

    for(const auto & screen : m_screen_map)
    {
        screen_vec.push_back(screen.first);
    }

    return screen_vec;
}

}
