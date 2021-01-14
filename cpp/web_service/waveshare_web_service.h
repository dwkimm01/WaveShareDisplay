//
// Created by Dave on 12/30/20.
//

#ifndef WSEINK_CPP_WAVESHARE_WEB_SERVICE_H
#define WSEINK_CPP_WAVESHARE_WEB_SERVICE_H

#include <memory>
#include <interfaces/i_screen_manager.h>

namespace waveshare_eink_cpp
{

class waveshare_web_service
{
public:
    waveshare_web_service
        ( std::shared_ptr<i_screen_mananger> screen_manager_ptr
        );

    ~waveshare_web_service();

private:
    std::shared_ptr<i_screen_mananger> m_screen_manager_ptr;
};

}
#endif //WSEINK_CPP_WAVESHARE_WEB_SERVICE_H
