#ifndef COMMON_H
#define COMMON_H

Magick::ColorRGB to_magick_color(color color) {
    return Magick::ColorRGB( 
        color.get_red()   / 255.0,
        color.get_green() / 255.0,
        color.get_blue()  / 255.0
    );
}

#endif