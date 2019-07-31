INCLUDE_DIR = ./include

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

EXEC = ./build/wallpaper

default: wallpaper

wallpaper: $(OBJECTS)
	g++ $(OBJECTS) -o $(EXEC) `Magick++-config --ldflags --libs`

build/%.o: src/%.cpp
	g++ -c $< -o $@ `Magick++-config --cppflags --libs` -I$(INCLUDE_DIR)

clean:
	-rm $(OBJECTS)
	-rm $(EXEC)

