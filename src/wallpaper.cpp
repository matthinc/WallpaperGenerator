#include <iostream>
#include <string>
#include <Magick++.h>
#include <sys/stat.h>

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

/**
 * Checks wether the provided filepath is valid, accessable and is
 * a file and not a directory.
 *
 * @param path Filepath to be checked for correctness
 * @return `true` when valid, `false` when invalid
 */
bool validate_filepath(const std::string& path) {
    struct stat fileinfo;
    if(stat(path.c_str(), &fileinfo)) {
        return false;
    }
    if(fileinfo.st_mode & S_IFDIR) {
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    Magick::InitializeMagick(*argv);

    auto arg_data = arguments::parse_args(argc, argv);

    if(arg_data.logo != nullptr && !validate_filepath(*arg_data.logo)) {
      std::cerr << "Invalid file '" << *arg_data.logo << "'" << std::endl;
      return 1;
    }

    // Create Wallpaper
    Magick::Image* image = make_wallpaper(arg_data);
    if (image != nullptr) {
        image->write(arg_data.outfile);
        delete image;
    }

    return 0;
}
