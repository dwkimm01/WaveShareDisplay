//
// Created by Dave on 1/10/21.
//

#ifndef WSEINK_CPP_BITMAPS_H
#define WSEINK_CPP_BITMAPS_H

#include <vector>
#include <string>

namespace waveshare_eink_cpp
{

class bitmaps
{
public:
    const std::vector<std::vector<bool>> & get(const std::string &name);
};

}
#endif //WSEINK_CPP_BITMAPS_H
