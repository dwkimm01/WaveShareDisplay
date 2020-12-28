
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
    // Defs
    enum color_t
    { d_WHITE = 0xFF
    , d_BLACK = 0x00
    };

    enum dot_pixel_t
    { d_DOT_PIXEL_1X1 = 1              // 1 x 1
    , d_DOT_PIXEL_2X2                  // 2 X 2
    , d_DOT_PIXEL_3X3                  // 3 X 3
    , d_DOT_PIXEL_4X4                  // 4 X 4
    , d_DOT_PIXEL_5X5                  // 5 X 5
    , d_DOT_PIXEL_6X6                  // 6 X 6
    , d_DOT_PIXEL_7X7                  // 7 X 7
    , d_DOT_PIXEL_8X8                  // 8 X 8
    , d_DOT_PIXEL_DFT = d_DOT_PIXEL_1X1  // Default dot pixel
    };

    enum dot_style_t
    { d_DOT_FILL_AROUND  = 1               // dot pixel 1 x 1
    , d_DOT_FILL_RIGHTUP                  // dot pixel 2 X 2
    , d_DOT_STYLE_DFT = d_DOT_FILL_AROUND
    } DOT_STYLE;


    enum line_style_t
    { d_LINE_STYLE_SOLID = 0
    , d_LINE_STYLE_DOTTED
    };

    enum draw_fill_t
    { d_DRAW_FILL_EMPTY = 0
    , d_DRAW_FILL_FULL
    };

    // Text
    static void Paint_DrawChar
        ( bitmap_image & img
        , const size_t Xpoint
        , const size_t Ypoint
        , const char Acsii_Char
        , sFONT* Font
        , const color_t Color_Foreground
        , const color_t Color_Background
        );

    static void Paint_DrawString_EN
        ( bitmap_image & img
        , const size_t Xstart
        , const size_t Ystart
        , const char * pString
        , sFONT* Font
        , const color_t Color_Foreground
        , const color_t Color_Background
        );

    // Lines and shapes
    static void Paint_DrawPoint
        ( bitmap_image & img
        , const size_t Xpoint
        , const size_t Ypoint
        , const color_t Color
        , const dot_pixel_t Dot_Pixel
        , const dot_style_t Dot_Style
        );

    static void Paint_DrawLine
        ( bitmap_image & img
        , const size_t Xstart
        , const size_t Ystart
        , const size_t Xend
        , const size_t Yend
        , const color_t Color
        , const dot_pixel_t Line_width
        , const line_style_t Line_Style
        );

    static void Paint_DrawRectangle
        ( bitmap_image & img
        , const size_t Xstart
        , const size_t Ystart
        , const size_t Xend
        , const size_t Yend
        , const color_t Color
        , const dot_pixel_t Line_width
        , const draw_fill_t Draw_Fill
        );

    static void Paint_DrawCircle
        ( bitmap_image & img
        , const size_t X_Center
        , const size_t Y_Center
        , const size_t Radius
        , const color_t Color
        , const dot_pixel_t Line_width
        , const draw_fill_t Draw_Fill
        );
};

}

#endif //WSEINK_CPP_DRAWING_H
