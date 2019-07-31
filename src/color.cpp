#include <string>
#include <cstdint>

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