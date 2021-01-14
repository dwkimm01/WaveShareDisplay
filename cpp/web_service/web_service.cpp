//
// Created by Dave on 1/14/21.
//

#include "web_service.h"
#include "drogon/drogon.h"

namespace waveshare_eink_cpp
{

void web_service::run_in_background()
{
    m_thread = std::thread([]()
            { drogon::app().run(); });
}

void web_service::quit()
{
    drogon::app().quit();
}

void web_service::join()
{
    if(m_thread.joinable())
    {
        m_thread.join();
    }
}

}