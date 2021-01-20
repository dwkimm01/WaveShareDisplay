//
// Created by Kimmel, David on 12/1/20.
//

#ifndef E_PAPER_BITMAPIMAGE_H
#define E_PAPER_BITMAPIMAGE_H

#include <vector>
#include <stdint.h>

namespace waveshare_eink_cpp
{

class bitmap_image
{
public:
    typedef uint16_t input_pixel_t;

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

    bitmap_image
        ( const size_t image_width_pixels
        , const size_t image_height_pixels
        , const mirror_t mirror
        , const rotate_t rotate
        , const uint16_t color
        );

    size_t image_width_pixels() const;
    size_t image_height_pixels() const;
    size_t bits_per_pixel() const;

    void set
        ( const size_t x
        , const size_t y
        , const input_pixel_t pixel_val
        );

    input_pixel_t get
        ( const size_t x
        , const size_t y
        ) const;

    void fill
        ( const input_pixel_t val
        );

    unsigned char const* data
        (
        ) const;


    // TODO fix these as they don't retroactively fix the screen
    mirror_t& mirror();
    mirror_t mirror() const;
    rotate_t& rotate();
    rotate_t rotate() const;

    bool has_updates(const bitmap_image & rhs) const;

private:
    uint16_t Width {0};
    uint16_t Height {0};
    uint16_t WidthMemory {0};
    uint16_t HeightMemory {0};
    mirror_t Mirror {MIRROR_NONE};
    rotate_t Rotate {ROT_0};
    uint16_t WidthByte {0};
    uint16_t HeightByte {0};
    uint16_t Scale {0};
    std::vector<unsigned char> m_pixel_data;
};

}
#endif //E_PAPER_BITMAPIMAGE_H
