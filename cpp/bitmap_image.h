//
// Created by Kimmel, David on 12/1/20.
//

#ifndef E_PAPER_BITMAPIMAGE_H
#define E_PAPER_BITMAPIMAGE_H

#include <vector>

namespace waveshare_eink_cpp
{

class bitmap_image
{
public:
    typedef uint16_t input_pixel_t;

    bitmap_image
        ( const size_t image_width_pixels
        , const size_t image_height_pixels
        , const uint16_t rotate
        , const uint16_t color
        );

    size_t image_width_pixels() const;
    size_t image_height_pixels() const;
    size_t bits_per_pixel() const;

    void set
        ( const size_t x
        , const size_t y
        , const input_pixel_t val
        );

    input_pixel_t get
        ( const size_t x
        , const size_t y
        ) const;

    void fill
        ( unsigned char v
        );

    unsigned char const* data
        (
        ) const;

    enum color_t
    { CWHITE = 0xFF
    , CBLACK = 0x00
    , CRED = 0x00
    };

    enum mirror_t
    { MIRROR_NONE = 0x00
    , MIRROR_HORIZONTAL = 0x01
    , MIRROR_VERTICAL = 0x02
    , MIRROR_ORIGIN = 0x03
    };

    enum rotate_t
    { ROT_0 = 0
    , ROT_90 = 90
    , ROT_180 = 180
    , ROT_270 = 270
    };

private:
    uint16_t Width;
    uint16_t Height;
    uint16_t WidthMemory;
    uint16_t HeightMemory;
    uint16_t Color;
    uint16_t Rotate;
    uint16_t Mirror;
    uint16_t WidthByte;
    uint16_t HeightByte;
    uint16_t Scale;
    std::vector<unsigned char> m_pixel_data;
};

}
#endif //E_PAPER_BITMAPIMAGE_H
