//
// Created by Kimmel, David on 12/1/20.
//
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "bitmap_image.h"

namespace waveshare_eink_cpp
{

bitmap_image::bitmap_image
    ( const size_t image_width_pixels
    , const size_t image_height_pixels
    , const mirror_t mirror
    , const rotate_t rotate
    , const uint16_t color
    ) : WidthMemory(image_width_pixels)
      , HeightMemory(image_height_pixels)
//      , Color(color)
      , Scale(2)
      , WidthByte((image_width_pixels % 8 == 0)? (image_width_pixels / 8 ): (image_width_pixels / 8 + 1))
      , HeightByte(image_height_pixels)
      , Mirror(mirror)
      , Rotate(rotate)
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
    , const input_pixel_t pixel_val
    )
{
    input_pixel_t val = pixel_val;
    if(Xpoint > Width || Ypoint > Height)
    {
        return; // Exceeding display boundaries
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
        return; // Exceeding display boundaries
    }

//    std::cout << "    SET(" << X << ", " << Y << ")" << std::endl;
    if(Scale == 2)
    {
        uint16_t Addr = X / 8 + Y * WidthByte;

        if(Addr >= m_pixel_data.size())
            return;

        uint16_t Rdata = m_pixel_data.at(Addr);
        if(val == CBLACK)
            m_pixel_data.at(Addr) = Rdata & ~(0x80 >> (X % 8));
        else
            m_pixel_data.at(Addr) = Rdata | (0x80 >> (X % 8));
    }else if(Scale == 4){
        uint32_t Addr = X / 4 + Y * WidthByte;

        if(Addr >= m_pixel_data.size())
            return;

        val = val % 4;//Guaranteed color scale is 4  --- 0~3
        uint8_t Rdata = m_pixel_data.at(Addr);

        Rdata = Rdata & (~(0xC0 >> ((X % 4)*2)));//Clear first, then set value
        m_pixel_data.at(Addr) = Rdata | ((val << 6) >> ((X % 4)*2));
    }else if(Scale == 7){
        uint32_t Addr = X / 2  + Y * WidthByte;

        if(Addr >= m_pixel_data.size())
            return;

        uint8_t Rdata = m_pixel_data.at(Addr);
        Rdata = Rdata & (~(0xF0 >> ((X % 2)*4)));//Clear first, then set value
        m_pixel_data.at(Addr) = Rdata | ((val << 4) >> ((X % 2)*4));
        // printf("Add =  %d ,data = %d\r\n",Addr,Rdata);
    }
}

bitmap_image::input_pixel_t bitmap_image::get
    ( const size_t Xpoint
    , const size_t Ypoint
    ) const
{
    const input_pixel_t off_image_val {0};
    if(Xpoint > Width || Ypoint > Height)
    {
        return off_image_val; // Exceeding display boundaries
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
            return off_image_val;
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
            return off_image_val;
    }

    if(X > WidthMemory || Y > HeightMemory)
    {
        return off_image_val; // Exceeding display boundaries
    }

    if(Scale == 2)
    {
        uint16_t Addr = X / 8 + Y * WidthByte;

        if(Addr >= m_pixel_data.size())
            return off_image_val;

        uint16_t Rdata = m_pixel_data.at(Addr);
        return Rdata & ~(0x80 >> (X % 8)); // TODO
//        if(val == CBLACK)
//            return Rdata & ~(0x80 >> (X % 8));
//        else
//            return Rdata | (0x80 >> (X % 8));
    }else if(Scale == 4){
        uint32_t Addr = X / 4 + Y * WidthByte;

        if(Addr >= m_pixel_data.size())
            return off_image_val;

//        val = val % 4;//Guaranteed color scale is 4  --- 0~3
        uint8_t Rdata = m_pixel_data.at(Addr);

        Rdata = Rdata & (~(0xC0 >> ((X % 4)*2)));//Clear first, then set value
        return Rdata | ((0xff << 6) >> ((X % 4)*2)); // TODO
//        m_pixel_data.at(Addr) = Rdata | ((val << 6) >> ((X % 4)*2));
    }else if(Scale == 7){
        uint32_t Addr = X / 2  + Y * WidthByte;

        if(Addr >= m_pixel_data.size())
            return off_image_val;

        uint8_t Rdata = m_pixel_data.at(Addr);
        return Rdata | ((0xff << 4) >> ((X % 2)*4)); // TODO
//        Rdata = Rdata & (~(0xF0 >> ((X % 2)*4)));//Clear first, then set value
//        m_pixel_data.at(Addr) = Rdata | ((val << 4) >> ((X % 2)*4));
        // printf("Add =  %d ,data = %d\r\n",Addr,Rdata);
    }

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

bitmap_image::mirror_t& bitmap_image::mirror() { return Mirror; }
bitmap_image::mirror_t bitmap_image::mirror() const { return Mirror; }
bitmap_image::rotate_t& bitmap_image::rotate() { return Rotate; }
bitmap_image::rotate_t bitmap_image::rotate() const { return Rotate; }


bool bitmap_image::has_updates(const bitmap_image & rhs) const
{
    if(m_pixel_data.size() != rhs.m_pixel_data.size())
    {
        std::cout << "Pixel data size is differenent, what?" << std::endl;
        return true;
    }
    for(int i = 0; i < m_pixel_data.size(); ++i)
    {
        if(m_pixel_data.at(i) != rhs.m_pixel_data.at(i))
        {
            std::cout << "pixel diff at " << i << std::endl;
            return true;
        }
    }
    std::cout << "No pixel diffs" << std::endl;
    return false;
}


}
