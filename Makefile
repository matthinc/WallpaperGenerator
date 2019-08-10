INCLUDE_DIR = ./include

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

CXXFLAGS = -Wall -pedantic -Wextra -Wconversion

EXEC = ./build/wallpaper

default: wallpaper

wallpaper: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) `Magick++-config --ldflags --libs`

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ `Magick++-config --cppflags --libs` -I$(INCLUDE_DIR)

clean:
	-rm $(OBJECTS)
	-rm $(EXEC)

