#include "position.h"

position::point position::by_string(std::string position, int maxw, int maxh, int objw, int objh, int edge_dist) {
    if (position == "center") {
        return {
            maxw / 2 - objw / 2,
            maxh / 2 - objh / 2
        };
    }
    if (position == "bottom_right") {
        return {
            maxw - objw - edge_dist,
            maxh - objh - edge_dist
        };
    }
    if (position == "bottom_left") {
        return {
            edge_dist,
            maxh - objh - edge_dist
        };
    }
    if (position == "top_right") {
        return {
            maxw - objw - edge_dist,
            edge_dist
        };
    }
    if (position == "top_left") {
        return {
            edge_dist,
            edge_dist
        };
    }
    return {0, 0};
}