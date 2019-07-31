#include <string>
#include <cstdint>

#ifndef COLOR_H
#define COLOR_H

class color {
    private:
        std::uint8_t c_r;
        std::uint8_t c_g;
        std::uint8_t c_b;
        std::int8_t hex_char_int(char);
    public:
        color();
        color(std::string);

        inline std::uint8_t get_red() { return c_r; };
        inline std::uint8_t get_green() { return c_g; };
        inline std::uint8_t get_blue() { return c_b; };

        std::string to_rgb_string();
};

#endif