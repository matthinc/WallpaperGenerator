#include <vector>
#include <string>

#include "color.h"

#ifndef COLOR_LIST_H
#define COLOR_LIST_H

#define COLOR_LIST_SEPARATOR_SYMBOL ';'

class color_list {
    private:
        std::vector<color> cvec;
    public:
        inline color_list() {};
        color_list(std::string);
        
        int size() const;
        color at(int) const;
};

#endif