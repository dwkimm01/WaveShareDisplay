//
// Created by Dave on 1/20/21.
//

#ifndef WSEINK_CPP_GIMP_MONKEY_IMAGE_H
#define WSEINK_CPP_GIMP_MONKEY_IMAGE_H

#include <cstddef>

namespace waveshare_eink_cpp
{

class gimp_monkey_image
{
public:
    size_t width();
    size_t height();

    unsigned char pixel_at(const size_t x, const size_t y);
};

}

#endif //WSEINK_CPP_GIMP_MONKEY_IMAGE_H
