#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

#include "color.h"

std::int8_t color::hex_char_int(char chr) {
    if (chr >= 0x30 && chr <= 0x39) return (chr - 0x30) & 0xFF; // 0-9
    if (chr >= 0x41 && chr <= 0x46) return (chr - 0x37) & 0xFF; // A-F
    if (chr >= 0x61 && chr <= 0x66) return (chr - 0x57) & 0xFF; // a-f
    return -1;
}

color::color() {
    c_r = 0x0;
    c_g = 0x0;
    c_b = 0x0;
}

color::color(std::string in) {
    c_r = 0x0;
    c_g = 0x0;
    c_b = 0x0;
    // 6 digit hex format #rrggbb
    if (in.size() == 7 && in[0] == '#') {
        c_r  = hex_char_int(in[1]) << 4;
        c_r |= hex_char_int(in[2]);
        c_g  = hex_char_int(in[3]) << 4;
        c_g |= hex_char_int(in[4]);
        c_b  = hex_char_int(in[5]) << 4;
        c_b |= hex_char_int(in[6]);
    }
    // 3 digit hex format #rgb
    if (in.size() == 4 && in[0] == '#') {
        c_r  = hex_char_int(in[1]);
        c_r |= c_r << 4;
        c_g  = hex_char_int(in[2]);
        c_g |= c_g << 4;
        c_b  = hex_char_int(in[3]);
        c_b |= c_b << 4;
    }
    if (in.size() == 10 && in[0] == '+') {
        // https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
        // https://www.programmingalgorithms.com/algorithm/hsv-to-rgb/cpp/
        double H = std::stof(in.substr(1, 3)); // [0,360)
        double S = std::stof(in.substr(4, 3)); // [0,1]
        double V = std::stof(in.substr(7, 3)); // [0,1]
        double h = std::max(static_cast<double>(0.0), std::min(static_cast<double>(360.0), H));
        double s = std::max(static_cast<double>(0.0), std::min(static_cast<double>(100.0), S));
        double v = std::max(static_cast<double>(0.0), std::min(static_cast<double>(100.0), V));
        s = s / 100;
        v = v / 100;

        double r = 0, g = 0, b = 0;

        if (s == 0) {
            r = v;
            g = v;
            b = v;
        }
        else {
            int i;
            double f, p, q, t;

            if (h == 360)
                h = 0;
            else
                h = h / 60;

            i = (int)trunc(h);
            f = h - i;

            p = v * (1.0 - s);
            q = v * (1.0 - (s * f));
            t = v * (1.0 - (s * (1.0 - f)));

            switch (i) {
            case 0:
                r = v;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = v;
                b = p;
                break;

            case 2:
                r = p;
                g = v;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = v;
                break;

            case 4:
                r = t;
                g = p;
                b = v;
                break;

            default:
                r = v;
                g = p;
                b = q;
                break;
            }
        }
        c_r = std::round(255 * r);
        c_g = std::round(255 * g);
        c_b = std::round(255 * b);
    }
}

std::string color::to_rgb_string() {
    std::string rgb{""};
    rgb.append(std::to_string(c_r));
    rgb.append(",");
    rgb.append(std::to_string(c_g));
    rgb.append(",");
    rgb.append(std::to_string(c_b));
    return rgb;
}