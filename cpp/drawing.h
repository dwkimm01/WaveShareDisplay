
//
// Created by Dave on 12/22/20.
//

#ifndef WSEINK_CPP_DRAWING_H
#define WSEINK_CPP_DRAWING_H

#include "bitmap_image.h"
#include "../c/lib/Fonts/fonts.h"

namespace waveshare_eink_cpp
{

class drawing
{
public:
    static void Paint_DrawChar
        ( bitmap_image & img
        , const size_t Xpoint
        , const size_t Ypoint
        , const char Acsii_Char
        , sFONT* Font
        , const size_t Color_Foreground
        , const size_t Color_Background
        );

    static void Paint_DrawString_EN
        ( bitmap_image & img
        , const size_t Xstart
        , const size_t Ystart
        , const char * pString
        , sFONT* Font
        , const size_t Color_Foreground
        , const size_t Color_Background
        );

};

}

#endif //WSEINK_CPP_DRAWING_H
