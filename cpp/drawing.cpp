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
    , const color_t Color_Foreground
    , const color_t Color_Background
    )
{

//#define WHITE          0xFF
//#define BLACK          0x00
//#define RED            BLACK

#define IMAGE_BACKGROUND    d_WHITE
#define FONT_FOREGROUND     d_BLACK
#define FONT_BACKGROUND     d_WHITE

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
    , const color_t Color_Foreground
    , const color_t Color_Background
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

void drawing::Paint_DrawPoint
    ( bitmap_image & img
    , const size_t Xpoint
    , const size_t Ypoint
    , const color_t Color
    , const dot_pixel_t Dot_Pixel
    , const dot_style_t Dot_Style
    )
{
    if (Xpoint > img.image_width_pixels() || Ypoint > img.image_height_pixels()) {
        // Debug("Paint_DrawPoint Input exceeds the normal display range\r\n");
        return;
    }

    int16_t XDir_Num , YDir_Num;
    if (Dot_Style == d_DOT_FILL_AROUND) {
        for (XDir_Num = 0; XDir_Num < 2 * Dot_Pixel - 1; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num < 2 * Dot_Pixel - 1; YDir_Num++) {
                if(Xpoint + XDir_Num - Dot_Pixel < 0 || Ypoint + YDir_Num - Dot_Pixel < 0)
                    break;
                // printf("x = %d, y = %d\r\n", Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel);
                img.set(Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, Color);
            }
        }
    } else {
        for (XDir_Num = 0; XDir_Num <  Dot_Pixel; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num <  Dot_Pixel; YDir_Num++) {
                img.set(Xpoint + XDir_Num - 1, Ypoint + YDir_Num - 1, Color);
            }
        }
    }
}


void drawing::Paint_DrawLine
    ( bitmap_image & img
    , const size_t Xstart
    , const size_t Ystart
    , const size_t Xend
    , const size_t Yend
    , const color_t Color
    , const dot_pixel_t Line_width
    , const line_style_t Line_Style
    )
{
    if (Xstart > img.image_width_pixels() || Ystart > img.image_height_pixels() ||
        Xend > img.image_width_pixels() || Yend > img.image_height_pixels())
    {
        // Debug("Paint_DrawLine Input exceeds the normal display range\r\n");
        return;
    }

    size_t Xpoint = Xstart;
    size_t Ypoint = Ystart;
    const int dx = (int)Xend - (int)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
    const int dy = (int)Yend - (int)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

    // Increment direction, 1 is positive, -1 is counter;
    int XAddway = Xstart < Xend ? 1 : -1;
    int YAddway = Ystart < Yend ? 1 : -1;

    //Cumulative error
    int Esp = dx + dy;
    char Dotted_Len = 0;

    for (;;) {
        Dotted_Len++;
        //Painted dotted line, 2 point is really virtual
        if (Line_Style == d_LINE_STYLE_DOTTED && Dotted_Len % 3 == 0) {
            //Debug("LINE_DOTTED\r\n");
            Paint_DrawPoint(img, Xpoint, Ypoint, IMAGE_BACKGROUND, Line_width, d_DOT_STYLE_DFT);
            Dotted_Len = 0;
        } else {
            Paint_DrawPoint(img, Xpoint, Ypoint, Color, Line_width, d_DOT_STYLE_DFT);
        }
        if (2 * Esp >= dy) {
            if (Xpoint == Xend)
                break;
            Esp += dy;
            Xpoint += XAddway;
        }
        if (2 * Esp <= dx) {
            if (Ypoint == Yend)
                break;
            Esp += dx;
            Ypoint += YAddway;
        }
    }
}

void drawing::Paint_DrawRectangle
    ( bitmap_image & img
    , const size_t Xstart
    , const size_t Ystart
    , const size_t Xend
    , const size_t Yend
    , const color_t Color
    , const dot_pixel_t Line_width
    , const draw_fill_t Draw_Fill
    )
{
    if (Xstart > img.image_width_pixels() || Ystart > img.image_height_pixels() ||
        Xend > img.image_width_pixels() || Yend > img.image_height_pixels())
    {
        // Debug("Input exceeds the normal display range\r\n");
        return;
    }

    if (Draw_Fill) {
        size_t Ypoint;
        for(Ypoint = Ystart; Ypoint < Yend; Ypoint++) {
            Paint_DrawLine(img, Xstart, Ypoint, Xend, Ypoint, Color , Line_width, d_LINE_STYLE_SOLID);
        }
    } else {
        Paint_DrawLine(img, Xstart, Ystart, Xend, Ystart, Color, Line_width, d_LINE_STYLE_SOLID);
        Paint_DrawLine(img, Xstart, Ystart, Xstart, Yend, Color, Line_width, d_LINE_STYLE_SOLID);
        Paint_DrawLine(img, Xend, Yend, Xend, Ystart, Color, Line_width, d_LINE_STYLE_SOLID);
        Paint_DrawLine(img, Xend, Yend, Xstart, Yend, Color, Line_width, d_LINE_STYLE_SOLID);
    }
}


void drawing::Paint_DrawCircle
    ( bitmap_image & img
    , const size_t X_Center
    , const size_t Y_Center
    , const size_t Radius
    , const color_t Color
    , const dot_pixel_t Line_width
    , const draw_fill_t Draw_Fill
    )
{
    if (X_Center > img.image_width_pixels() || Y_Center >= img.image_height_pixels()) {
        // Debug("Paint_DrawCircle Input exceeds the normal display range\r\n");
        return;
    }

    //Draw a circle from(0, R) as a starting point
    int16_t XCurrent, YCurrent;
    XCurrent = 0;
    YCurrent = Radius;

    //Cumulative error,judge the next point of the logo
    int16_t Esp = 3 - (Radius << 1 );

    int16_t sCountY;
    if (Draw_Fill == d_DRAW_FILL_FULL) {
        while (XCurrent <= YCurrent ) { //Realistic circles
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
                Paint_DrawPoint(img, X_Center + XCurrent, Y_Center + sCountY, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//1
                Paint_DrawPoint(img, X_Center - XCurrent, Y_Center + sCountY, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//2
                Paint_DrawPoint(img, X_Center - sCountY, Y_Center + XCurrent, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//3
                Paint_DrawPoint(img, X_Center - sCountY, Y_Center - XCurrent, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//4
                Paint_DrawPoint(img, X_Center - XCurrent, Y_Center - sCountY, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//5
                Paint_DrawPoint(img, X_Center + XCurrent, Y_Center - sCountY, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//6
                Paint_DrawPoint(img, X_Center + sCountY, Y_Center - XCurrent, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//7
                Paint_DrawPoint(img, X_Center + sCountY, Y_Center + XCurrent, Color, d_DOT_PIXEL_DFT, d_DOT_STYLE_DFT);//8
            }
            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    } else { //Draw a hollow circle
        while (XCurrent <= YCurrent ) {
            Paint_DrawPoint(img, X_Center + XCurrent, Y_Center + YCurrent, Color, Line_width, d_DOT_STYLE_DFT);//1
            Paint_DrawPoint(img, X_Center - XCurrent, Y_Center + YCurrent, Color, Line_width, d_DOT_STYLE_DFT);//2
            Paint_DrawPoint(img, X_Center - YCurrent, Y_Center + XCurrent, Color, Line_width, d_DOT_STYLE_DFT);//3
            Paint_DrawPoint(img, X_Center - YCurrent, Y_Center - XCurrent, Color, Line_width, d_DOT_STYLE_DFT);//4
            Paint_DrawPoint(img, X_Center - XCurrent, Y_Center - YCurrent, Color, Line_width, d_DOT_STYLE_DFT);//5
            Paint_DrawPoint(img, X_Center + XCurrent, Y_Center - YCurrent, Color, Line_width, d_DOT_STYLE_DFT);//6
            Paint_DrawPoint(img, X_Center + YCurrent, Y_Center - XCurrent, Color, Line_width, d_DOT_STYLE_DFT);//7
            Paint_DrawPoint(img, X_Center + YCurrent, Y_Center + XCurrent, Color, Line_width, d_DOT_STYLE_DFT);//8

            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    }
}

}
