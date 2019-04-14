DiAn Digital Image Processing
========
DiAn Digital Image Processing(DADIP) is the open-source image processing library. It is targeted to build on multi platform/Os. It supports some common image processing library.

# Features
- BMP format: Windows and OS/2 bitmap headers, 8/24 bits per pixel
- Convert: RGB to GrayScale image
- Filter: Median Filter, a single mask filter
- Geometry: Invert, Stretch, Crop, Paste, Geometry(Displacement, Stretching, Rotation)
- Histogram: Calculate histogram, histogram equalization
- Mathematic: AND, OR, XOR, NOT, NAND, NOR, ADD, SUBTRACT
- Overlay: non zero, zero, greater, less, average
- Rotate: 90/180/270/any origin, flip vertical, flip horizontal
- Warping: Warp, Object Warp

# OS Support
- Windows 32/64-bit
- Linux 32/64-bit

# Sample Workspace
For quickly manipulate with this library, we provide simple application that Invert res/sala.bmp

Visual Studio 2015
------------------
Use to build for Windows. Location: build/SampleWS/VS2015
1. Open VS2015.sln
2. Change input image at: Property -> Configuration Properties -> Debugging -> Command Arguments

Makefile
--------
Use to build for Linux. Location: build/SampleWS/makefile
1. Opens terminal and changes your working directory to DiAnDigitalImageProcessing package  
$ cd ${work}/build/SampleWS/makefile
2. Run make  
$ make
3. Run SampleWS  
$ ./SampleWS ../../../res/sala.bmp output.bmp

# Using the Source
- `app`: Application that uses DADIP library
- `build`: build system for DADIP libary
- `include`: header files
- `res`: source files that implement DADIP library
- `source`: image files

# License
Apache License, Version 2.0, see `LICENSE` file for details.
