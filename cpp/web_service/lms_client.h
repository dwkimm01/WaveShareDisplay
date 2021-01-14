//
// Created by Dave on 1/13/21.
//

#ifndef WSEINK_CPP_LMS_CLIENT_H
#define WSEINK_CPP_LMS_CLIENT_H

namespace waveshare_eink_cpp
{

class lms_client {
public:
    lms_client();

    void play();

    std::string currently_playing();

};

}
#endif //WSEINK_CPP_LMS_CLIENT_H
