//
// Created by Dave on 1/9/21.
//

#include <iostream>
#include "screen_manager.h"

namespace waveshare_eink_cpp
{

screen_manager::screen_manager(std::shared_ptr<i_bitmap_display> bitmap_display_ptr)
    : m_bitmap_display_ptr(bitmap_display_ptr)
    , m_img_a(bitmap_display_ptr->create_image())
    , m_img_b(bitmap_display_ptr->create_image())
{
    // When starting up give m_img_a something different to force an update
    m_img_a.fill(50); // nothing uses 50, yeah bad sentinel value should be defined somewhere
}

screen_manager::~screen_manager()
{}

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
    std::cout << "screen manager draw current screen" << std::endl;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_current_screen)
        {
            std::cout << "No current screen to draw" << std::endl;
            return false;
        }

        // Draw to m_img_b first
        m_current_screen->draw(m_img_b);
    }

    std::cout << "screen manager draw current screen, done" << std::endl;
    return true;
}

bool screen_manager::send_to_display
    (
    )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_bitmap_display_ptr)
    {
        std::cout << "No bitmap display to send img to" << std::endl;
        return false;
    }

    if(m_img_b.has_updates(m_img_a))
    {
        std::cout << "Copying updated screen" << std::endl;
        m_img_a = m_img_b;
        std::cout << "Copying updated screen, done" << std::endl;
        m_bitmap_display_ptr->display(m_img_a);
    }

    return true;
}

bool screen_manager::clear_current_screen
    ( const uint8_t val
    )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_bitmap_display_ptr)
        return false;

    m_img_a.fill(val);
    m_img_b.fill(val);
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
