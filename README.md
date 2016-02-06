# SF Game

This project is a playground for making a game / game engine with SFML library.
Target of this project is a simple space-shooter game or simmilar, nothing fancy,
just a test game for the game engine.

### Configuration and build
The project is considered to be compiled for GNU/Linux with GNU or Clang C++ compilers.
Building for other platforms is not yet supported, however, the codebase is designed to
be as portable as possible.

To build, please follow these steps:
* `$ mkdir build`
* `$ cd build`
* `$ cmake .. (optionally specify build type -DCMAKE_BUILD_TYPE=[Debug, Release])`
* `$ make -j`

To select a compiler (GNU C++ or Clang), set the value CXX while running cmake, e.g.
* `$ CXX=/usr/bin/clang++ cmake ..`

### Running
To run the game just type:
* `$ ./sf_game`

Available options:  
`  -h [ --help ]           Prints the help message`  
`  -f [ --full-screen ] `  
`  -r [ --resolution ] arg Game resolution`
