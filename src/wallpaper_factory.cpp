#include "wallpaper_factory.h"
#include "position.h"
#include "common.h"

#include <Magick++.h>
#include <string>
#include <list>

Magick::Image* wallpaper_factory::get_base_wallpaper(
    int screenw,
    int screenh,
    std::string& type,
    color_list& colors
) {
    /*
        SOLID
        colors: 1
    */
    if (type == "solid") {
        return new Magick::Image(
            Magick::Geometry(screenw, screenh),
            to_magick_color(colors.at(0))
        );
    }
    /*
        RADIAL GRADIENT
        colors: 2
    */
    if (type == "radial_gradient") {
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
    /*
        LINEAR GRADIENT
        colors: 2
    */
    if (type == "linear_gradient") {
        std::string gradient{"gradient:rgb("};
        gradient.append(colors.at(0).to_rgb_string());
        gradient.append(")-rgb(");
        gradient.append(colors.at(1).to_rgb_string());
        gradient.append(")");

        Magick::Image* image = new Magick::Image();
        image->size(Magick::Geometry(screenw, screenh));
        image->read(gradient);
        return image;
    }
    /*
        VERTICAL SPLIT
        colors: 1-n
    */
    if (type == "vertical_split") {
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
    /*
        HORIZONTAL SPLIT
        colors: 1-n
    */
    if (type == "horizontal_split") {
        Magick::Image* image = new Magick::Image();
        image->size(Magick::Geometry(screenw, screenh));
        image->strokeWidth(0);

        int number_of_colors = colors.size();

        for (int i = 0; i < number_of_colors; i++) {
            Magick::ColorRGB fill_color = to_magick_color(colors.at(i));
            image->fillColor(fill_color);
            image->draw(Magick::DrawableRectangle(
                (screenw / number_of_colors) * i,
                0,
                (screenw / number_of_colors) * (i + 1),
                screenh
            ));
        }

        return image;
    }
    /*
        DIAGONAL SPLIT
        colors: 2
    */
    if (type == "diagonal_split") {
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
        logo_image.resize(
            Magick::Geometry(
                (logo_image.columns() * logo_scale) / 100,
                (logo_image.rows() * logo_scale) / 100
            )
        );
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