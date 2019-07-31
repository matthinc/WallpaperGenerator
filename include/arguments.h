#include <string>

#include "color.h"
#include "color_list.h"

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

namespace arguments {
    typedef struct {
        std::string* type;
        color_list colors;
        std::string outfile{"wallpaper.png"};
        int screenw{1920};
        int screenh{1080};
        std::string* logo;
        std::string logo_position{"center"};
        int logo_scale{100};
        std::string* image;
    } args;

    args parse_args(int argc, char** argv);
}

#endif