#include "wallpaper_factory.h"
#include "position.h"
#include "common.h"

#include <Magick++.h>
#include <string>
#include <list>

Magick::Image* make_solid(int screenw, int screenh, color_list& colors) {
    return new Magick::Image(
        Magick::Geometry(screenw, screenh),
        to_magick_color(colors.at(0))
    );
}

Magick::Image* make_radial_gradient(int screenw, int screenh, color_list& colors) {
    std::string gradient{"radial-gradient:rgb("};
    gradient.append(colors.at(0).to_rgb_string());
    gradient.append(")-rgb(");
    gradient.append(colors.at(1).to_rgb_string());
    gradient.append(")");

    Magick::Image* image = new Magick::Image();
    image->size(Magick::Geometry(screenw, screenh));
    image->read(gradient);
    return image;
}

Magick::Image* make_linear_gradient(int screenw, int screenh, color_list& colors) {
    std::string gradient{"radial-gradient:rgb("};
    gradient.append(colors.at(0).to_rgb_string());
    gradient.append(")-rgb(");
    gradient.append(colors.at(1).to_rgb_string());
    gradient.append(")");

    Magick::Image* image = new Magick::Image();
    image->size(Magick::Geometry(screenw, screenh));
    image->read(gradient);
    return image;
}

Magick::Image* make_vertical_split(int screenw, int screenh, color_list& colors) {
    Magick::Image* image = new Magick::Image();
    image->size(Magick::Geometry(screenw, screenh));
    image->strokeWidth(0);
    int number_of_colors = colors.size();
    for (int i = 0; i < number_of_colors; i++) {
        Magick::ColorRGB fill_color = to_magick_color(colors.at(i));
        image->fillColor(fill_color);
        image->draw(Magick::DrawableRectangle(
            0,
            (screenh / number_of_colors) * i,
            screenw,
            (screenh / number_of_colors) * (i + 1)
        ));
    }
    return image;
}

Magick::Image* make_horizontal_split(int screenw, int screenh, color_list& colors) {
    Magick::Image* image = new Magick::Image();
    image->size(Magick::Geometry(screenw, screenh));
    image->strokeWidth(0);
    int number_of_colors = colors.size();
    for (int i = 0; i < number_of_colors; i++) {
        Magick::ColorRGB fill_color = to_magick_color(colors.at(i));
        image->fillColor(fill_color);
        image->draw(Magick::DrawableRectangle(
            0,
            (screenh / number_of_colors) * i,
            screenw,
            (screenh / number_of_colors) * (i + 1)
        ));
    }
    return image;
}

Magick::Image* make_diagonal_split(int screenw, int screenh, color_list& colors) {
    Magick::Image* image = new Magick::Image();
    image->size(Magick::Geometry(screenw, screenh));
    image->strokeWidth(0);
    image->fillColor(to_magick_color(colors.at(0)));
    {
        std::list<Magick::Coordinate> coords;
        coords.push_back(Magick::Coordinate(0, 0));
        coords.push_back(Magick::Coordinate(screenw, screenh));
        coords.push_back(Magick::Coordinate(0, screenh));

        image->draw(Magick::DrawablePolygon(coords));
    }
    image->fillColor(to_magick_color(colors.at(1)));
    {
        std::list<Magick::Coordinate> coords;
        coords.push_back(Magick::Coordinate(0, 0));
        coords.push_back(Magick::Coordinate(screenw, 0));
        coords.push_back(Magick::Coordinate(screenw, screenh));

        image->draw(Magick::DrawablePolygon(coords));
    }
    return image;
}

Magick::Image* wallpaper_factory::get_base_wallpaper(
    int screenw,
    int screenh,
    std::string& type,
    color_list& colors
) {
    if (type == "solid") {
        return make_solid(screenw, screenh, colors);
    }
    if (type == "radial_gradient") {
        return make_radial_gradient(screenw, screenh, colors);
    }
    if (type == "linear_gradient") {
        return make_linear_gradient(screenw, screenh, colors);
    }
    if (type == "vertical_split") {
        return make_vertical_split(screenw, screenh, colors);
    }
    if (type == "horizontal_split") {
        return make_horizontal_split(screenw, screenh, colors);
    }
    if (type == "diagonal_split") {
        return make_diagonal_split(screenw, screenh, colors);
    }
    return nullptr;
}

void wallpaper_factory::with_logo(
    Magick::Image* base,
    int screenw,
    int screenh,
    std::string& logo,
    int logo_scale,
    std::string& logo_position
) {
    Magick::Image logo_image;
    logo_image.read(logo);

    if (logo_scale != 100) {
        int width = (logo_image.columns() * logo_scale) / 100;
        int height = (logo_image.rows() * logo_scale) / 100;
        auto geometry = Magick::Geometry(width, height);
        logo_image.resize(geometry);
    }

    position::point pos = position::by_string(
        logo_position,
        screenw,
        screenh,
        logo_image.columns(),
        logo_image.rows(),
        LOGO_EDGE_DISTANCE
    );

    base->composite(logo_image, pos.x, pos.y, Magick::AtopCompositeOp);
}