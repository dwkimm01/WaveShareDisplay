//
// Created by Dave on 1/10/21.
//

#include "bitmaps.h"

namespace waveshare_eink_cpp
{

const std::vector<std::vector<bool>> def;

// Play
const std::vector<std::vector<bool>> bitmap_play =
    {{0,0,0,0,1,0,0,0,0},
     {0,0,0,0,1,1,0,0,0},
     {0,0,0,0,1,1,1,0,0},
     {0,0,0,0,1,1,1,1,0},
     {0,0,0,0,1,1,1,1,1},
     {0,0,0,0,1,1,1,1,0},
     {0,0,0,0,1,1,1,0,0},
     {0,0,0,0,1,1,0,0,0},
     {0,0,0,0,1,0,0,0,0}};

const std::vector<std::vector<bool>> & bitmaps::get(const std::string &name)
{
   if(name == "play")
   {
        return bitmap_play;
   }
   // else
   return def;
}

}