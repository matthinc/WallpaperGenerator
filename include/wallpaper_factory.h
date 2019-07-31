#include <Magick++.h>
#include <string>

#include "color_list.h"
#include "color.h"

#ifndef WALLPAPER_FACTORY_H
#define WALLPAPER_FACTORY_H

#define LOGO_EDGE_DISTANCE 50

namespace wallpaper_factory {
    Magick::Image* get_base_wallpaper(
        int screenw,
        int screenh,
        std::string& type,
        color_list& colors
    );

    void with_logo(
        Magick::Image* base,
        int screenw,
        int screenh,
        std::string& logo,
        int logo_scale,
        std::string& logo_position
    );
}

#endif