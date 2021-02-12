//
// Created by Dave on 1/13/21.
//

#ifndef WSEINK_CPP_LMS_CLIENT_H
#define WSEINK_CPP_LMS_CLIENT_H

namespace waveshare_eink_cpp
{

class lms_client {
public:
    lms_client
        ( const std::string & url = "http://localhost:9000"
        , const std::string & player_name = "jmba"
        );

    void play();

    void pause();

    std::string currently_playing();

private:
    std::string m_url;
    std::string m_player_name;
};

}
#endif //WSEINK_CPP_LMS_CLIENT_H
