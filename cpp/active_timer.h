//
// Created by Dave on 1/14/21.
//

#ifndef WSEINK_CPP_ACTIVE_TIMER_H
#define WSEINK_CPP_ACTIVE_TIMER_H

#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

namespace waveshare_eink_cpp
{

class active_timer
{
public:
    active_timer
        ( const std::chrono::milliseconds timeout_ms
        , std::function<void()> event_callback
        , std::function<bool()> should_sleep = [](){return true;}
        ) : m_timeout_ms(timeout_ms)
          , m_event_callback(event_callback)
          , m_should_sleep(should_sleep)
          , m_thread([&](){ run_loop(); })
    {
    }

    ~active_timer()
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_shutdown = true;
            m_cv.notify_all();
        }

        if(m_thread.joinable())
        {
            m_thread.join();
        }
    }

private:
    bool m_shutdown {false};
    std::chrono::milliseconds m_timeout_ms;
    std::function<void()> m_event_callback;
    std::function<bool()> m_should_sleep;

    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::thread m_thread;

    void run_loop()
    {
        while(true)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait_for(lock, m_timeout_ms, [&](){ return m_shutdown || !m_should_sleep(); });

            if(m_shutdown)
                return;

            if(m_event_callback)
            {
                try
                {
                    m_event_callback();
                }
                catch(const std::exception &e)
                {
                    std::cerr << "Exception in active timer callback " << e.what() << "\n";
                }
            }
        }
    }
};

}

#endif //WSEINK_CPP_ACTIVE_TIMER_H
