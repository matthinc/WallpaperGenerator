#include <algorithm>
#include <sstream>
#include <iostream>

#include "color_list.h"

color_list::color_list(std::string input) {
    if (std::count(input.begin(), input.end(), COLOR_LIST_SEPARATOR_SYMBOL) == 0) {
        cvec.push_back(color(input));
    } else {
        std::stringstream stream(input);
        std::string item;
        while (std::getline(stream, item, COLOR_LIST_SEPARATOR_SYMBOL)) {
            cvec.push_back(color(item));
        }
    }
}

color color_list::at(int at) const {
    if (at >= cvec.size()) return color();
    return cvec.at(at);
}

int color_list::size() const {
    return cvec.size();
}