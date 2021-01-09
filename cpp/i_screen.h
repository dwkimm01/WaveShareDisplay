//
// Created by Dave on 1/6/21.
//

#ifndef WSEINK_CPP_I_SCREEN_H
#define WSEINK_CPP_I_SCREEN_H

class i_screen
{
public:
    virtual ~i_screen() {}

    virtual void update_screen() = 0;
};


#endif //WSEINK_CPP_I_SCREEN_H
