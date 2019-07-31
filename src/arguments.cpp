#include "arguments.h"

#include <getopt.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdlib.h> 

const option long_options[] = {
    {"type", required_argument, NULL, 't'},
    {"bgcolor", optional_argument, NULL, 'c'},
    {"out", optional_argument, NULL, 'o'},
    {"width", optional_argument, NULL, 'w'},
    {"height", optional_argument, NULL, 'h'},
    {"logo", optional_argument, NULL, 'l'},
    {"logo_position", optional_argument, NULL, 'p'},
    {"logo_scale", optional_argument, NULL, 's'},
    {"image", optional_argument, NULL, 'i'}
};

arguments::args arguments::parse_args(int argc, char** argv) {
    arguments::args data;

    data.logo = nullptr;
    data.type = nullptr;
    data.image = nullptr;

    int option_index = 0;
    int argument;
    while ((argument = getopt_long(argc, argv, "t:c:o:w:h:l:p:s:", long_options, &option_index)) != -1) {
        switch (argument) {
            case 't':
                data.type = new std::string(optarg);
                break;
            case 'c':
                data.colors = color_list(optarg);
                break;
            case 'o':
                data.outfile = optarg;
                break;
            case 'w':
                data.screenw = std::atoi(optarg);
                break;
            case 'h':
                data.screenh = std::atoi(optarg);
                break;
            case 'l':
                data.logo = new std::string(optarg);
                break;
            case 'p':
                data.logo_position = optarg;
                break;
            case 's':
                data.logo_scale = std::atoi(optarg);
                break;
            case 'i':
                data.image = new std::string(optarg);
                break;
        }
    }

    if (data.type == nullptr) {
        std::cout << "Required parameter t (--type)" << std::endl;
        exit(1);
    }

    return data;
}