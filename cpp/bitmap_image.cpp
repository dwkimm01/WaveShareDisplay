//
// Created by Kimmel, David on 12/1/20.
//

#include <algorithm>
#include <stdexcept>
#include "bitmap_image.h"

namespace waveshare_eink_cpp
{

bitmap_image::bitmap_image
    ( const size_t image_width_pixels
    , const size_t image_height_pixels
    , const uint16_t rotate
    , const uint16_t color
    ) : WidthMemory(image_width_pixels)
      , HeightMemory(image_height_pixels)
      , Color(color)
      , Scale(2)
      , WidthByte((image_width_pixels % 8 == 0)? (image_width_pixels / 8 ): (image_width_pixels / 8 + 1))
      , HeightByte(image_height_pixels)
      , Rotate(rotate)
      , Mirror(MIRROR_NONE)
{
    if(Rotate == ROT_0 || Rotate == ROT_180)
    {
        Width = image_width_pixels;
        Height = image_height_pixels;
    }
    else
    {
        Width = image_height_pixels;
        Height = image_width_pixels;
    }

    m_pixel_data.resize(WidthByte * HeightByte);
    std::fill(m_pixel_data.begin(), m_pixel_data.end(), 0);
}

size_t bitmap_image::image_width_pixels() const { return Width; }
size_t bitmap_image::image_height_pixels() const { return Height; }
size_t bitmap_image::bits_per_pixel() const { return 8; } // TODO

void bitmap_image::set
    ( const size_t Xpoint
    , const size_t Ypoint
    , const input_pixel_t val
    )
{
    if(Xpoint > Width || Ypoint > Height)
    {
        //throw std::runtime_error("Exceeding display boundaries");
    }
    uint16_t X, Y;
    switch(Rotate) {
        case 0:
            X = Xpoint;
            Y = Ypoint;
            break;
        case 90:
            X = WidthMemory - Ypoint - 1;
            Y = Xpoint;
            break;
        case 180:
            X = WidthMemory - Xpoint - 1;
            Y = HeightMemory - Ypoint - 1;
            break;
        case 270:
            X = Ypoint;
            Y = HeightMemory - Xpoint - 1;
            break;
        default:
            return;
    }

    switch(Mirror) {
        case MIRROR_NONE:
            break;
        case MIRROR_HORIZONTAL:
            X = WidthMemory - X - 1;
            break;
        case MIRROR_VERTICAL:
            Y = HeightMemory - Y - 1;
            break;
        case MIRROR_ORIGIN:
            X = WidthMemory - X - 1;
            Y = HeightMemory - Y - 1;
            break;
        default:
            return;
    }

    if(X > WidthMemory || Y > HeightMemory)
    {
        //throw std::runtime_error("Exceeding display boundaries");
    }

    if(Scale == 2)
    {
        uint16_t Addr = X / 8 + Y * WidthByte;
        uint16_t Rdata = m_pixel_data.at(Addr);
        if(Color == CBLACK)
            m_pixel_data.at(Addr) = Rdata & ~(0x80 >> (X % 8));
        else
            m_pixel_data.at(Addr) = Rdata | (0x80 >> (X % 8));
    }else if(Scale == 4){
        uint32_t Addr = X / 4 + Y * WidthByte;
        Color = Color % 4;//Guaranteed color scale is 4  --- 0~3
        uint8_t Rdata = m_pixel_data.at(Addr);

        Rdata = Rdata & (~(0xC0 >> ((X % 4)*2)));//Clear first, then set value
        m_pixel_data.at(Addr) = Rdata | ((Color << 6) >> ((X % 4)*2));
    }else if(Scale == 7){
        uint32_t Addr = X / 2  + Y * WidthByte;
        uint8_t Rdata = m_pixel_data.at(Addr);
        Rdata = Rdata & (~(0xF0 >> ((X % 2)*4)));//Clear first, then set value
        m_pixel_data.at(Addr) = Rdata | ((Color << 4) >> ((X % 2)*4));
        // printf("Add =  %d ,data = %d\r\n",Addr,Rdata);
    }
}

bitmap_image::input_pixel_t bitmap_image::get
    ( const size_t x
    , const size_t y
    ) const
{
    // TODO
    return 0;
}

void bitmap_image::fill(const input_pixel_t val)
{
    for(int y = 0; y < Height; ++y)
    {
        for(int x = 0; x < Width; ++x)
        {
            set(x, y, val);
        }
    }
}

unsigned char const* bitmap_image::data
    (
    ) const
{
    return m_pixel_data.data();
}


}
