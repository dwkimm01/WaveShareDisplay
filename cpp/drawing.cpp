//
// Created by Dave on 12/22/20.
//

#include "drawing.h"

namespace waveshare_eink_cpp
{


void drawing::Paint_DrawChar
    ( bitmap_image & img
    , const size_t Xpoint
    , const size_t Ypoint
    , const char Acsii_Char
    , sFONT* Font
    , const size_t Color_Foreground
    , const size_t Color_Background
    )
{

#define WHITE          0xFF
#define BLACK          0x00
#define RED            BLACK

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK
#define FONT_BACKGROUND     WHITE

    size_t Page, Column;

    if (Xpoint > img.image_width_pixels() || Ypoint > img.image_height_pixels()) {
        //Debug("Paint_DrawChar Input exceeds the normal display range\r\n");
        return;
    }

    uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
    const unsigned char *ptr = &Font->table[Char_Offset];

    for (Page = 0; Page < Font->Height; Page ++ ) {
        for (Column = 0; Column < Font->Width; Column ++ ) {

            //To determine whether the font background color and screen background color is consistent
            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                if (*ptr & (0x80 >> (Column % 8)))
                    img.set(Xpoint + Column, Ypoint + Page, Color_Foreground);
                // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            } else {
                if (*ptr & (0x80 >> (Column % 8))) {
                    img.set(Xpoint + Column, Ypoint + Page, Color_Foreground);
                    // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                } else {
                    img.set(Xpoint + Column, Ypoint + Page, Color_Background);
                    // Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                }
            }
            //One pixel is 8 bits
            if (Column % 8 == 7)
                ptr++;
        }// Write a line
        if (Font->Width % 8 != 0)
            ptr++;
    }// Write all
}


void drawing::Paint_DrawString_EN
    ( bitmap_image & img
    , const size_t Xstart
    , const size_t Ystart
    , const char * pString
    , sFONT* Font
    , const size_t Color_Foreground
    , const size_t Color_Background
    )
{
    size_t Xpoint = Xstart;
    size_t Ypoint = Ystart;

    if (Xstart > img.image_width_pixels() || Ystart > img.image_height_pixels()) {
//        Debug("Paint_DrawString_EN Input exceeds the normal display range\r\n");
        return;
    }

    while (* pString != '\0') {
        //if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the Height of the character
        if ((Xpoint + Font->Width ) > img.image_width_pixels()) {
            Xpoint = Xstart;
            Ypoint += Font->Height;
        }

        // If the Y direction is full, reposition to(Xstart, Ystart)
        if ((Ypoint  + Font->Height ) > img.image_height_pixels() ) {
            Xpoint = Xstart;
            Ypoint = Ystart;
        }
        drawing::Paint_DrawChar(img, Xpoint, Ypoint, * pString, Font, Color_Background, Color_Foreground);

        //The next character of the address
        pString ++;

        //The next word of the abscissa increases the font of the broadband
        Xpoint += Font->Width;
    }
}


}
