# WallpaperGenerator

A lightweight CLI tool to generate wallpapers in a scriptable way.

[![Build Status](https://travis-ci.org/matthinc/WallpaperGenerator.svg?branch=master)](https://travis-ci.org/matthinc/WallpaperGenerator)
![GitHub issues](https://img.shields.io/github/issues/matthinc/WallpaperGenerator)

## Arguments

```
-t, --type          Wallpaper background type
-o, --out           Output filename

-w, --width
-h, --height        Size (Default 1920x1080)

-c, --bgcolor       List of colors
                    Format "#000000;#FF00FF;..."
                    Default "#000000"

-l, --logo          Logo path
-s, --logo_scale    Logo scaling in % (0-100, default 100)
-p, --logo_position Logo Position
                    (center, bottom_right, bottom_left,
                    top_right, top_left)
                    Default: center
```


## Types

### Solid
    wallpaper -t solid -c "#bfd3f2" -l arch.png
![...](examples/solid.png)

### Linear Gradient
    wallpaper -t linear_gradient -c "#bfd3f2;#8dabd9" -l arch.png
![...](examples/linear.png)

### Radial Gradient
    wallpaper -t radial_gradient -c "#bfd3f2;#8dabd9" -l arch.png
![...](examples/radial.png)

### Horizontal Split
    wallpaper -t horizontal_split -c "#bfd3f2;#8dabd9;#5c83bf;#4772b3" -l arch.png
![...](examples/horizontal.png)

### Vertical Split
    wallpaper -t vertical_split -c "#bfd3f2;#8dabd9;#5c83bf;#4772b3" -l arch.png
![...](examples/vertical.png)

### Diagonal Split
    wallpaper -t diagonal_split -c "#bfd3f2;#8dabd9" -l arch.png
![...](examples/diagonal.png)

### Triangle
    wallpaper -t triangle -c "#bfd3f2;#8dabd9" -l arch.png
![...](examples/triangle.png)

### Diamonds
    wallpaper -t diamonds -c "#bfd3f2;#8dabd9" -l arch.png
![...](examples/diamonds.png)


