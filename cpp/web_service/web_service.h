//
// Created by Dave on 1/14/21.
//

#ifndef WSEINK_CPP_WEB_SERVICE_H
#define WSEINK_CPP_WEB_SERVICE_H

#include <thread>

namespace waveshare_eink_cpp
{

class web_service
{
public:
    void run_in_background();

    bool is_running();

    void quit();

    void join();

private:
    std::thread m_thread;
};

}
#endif //WSEINK_CPP_WEB_SERVICE_H
