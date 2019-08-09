#include <iostream>
#include <string>
#include <Magick++.h>

#include "color.h"
#include "arguments.h"
#include "wallpaper_factory.h"

Magick::Image* make_wallpaper(arguments::args data) {
    Magick::Image* image = wallpaper_factory::get_base_wallpaper(
        data.screenw,
        data.screenh,
        *data.type,
        data.colors
    );

    if (image != nullptr && data.logo != nullptr) {
        wallpaper_factory::with_logo(
            image,
            data.screenw,
            data.screenh,
            *data.logo,
            data.logo_scale,
            data.logo_position
        );
    }

    if (image == nullptr) std::cerr << "Invalid type" << std::endl;
    return image;
}

int main(int argc, char** argv) {
    Magick::InitializeMagick(*argv);

    auto arg_data = arguments::parse_args(argc, argv);

    // Create Wallpaper
    Magick::Image* image = make_wallpaper(arg_data);
    if (image != nullptr) {
        image->write(arg_data.outfile);
        delete image;
    }

    return 0;
}
