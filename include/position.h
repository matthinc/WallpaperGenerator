#include <string>

#ifndef POSITION_H
#define POSITION_H

namespace position {
    typedef struct {
        int x, y;
    } point;

    point by_string(std::string position, int maxw, int maxh, int objw, int objh, int edge_dist = 0);
}

#endif