# Bloq
A cross-platform 2d game engine.

## Building
### Linux
You need the prerequisite libraries for SDL and its sub-libs (image, mixer, net, and ttf).

These libraries are included in lib/ with a makefile to build all as static libraries which get placed in lib/build/...
The makefile is designed to avoid rebuilding a given library if the .a file exists. To force a rebuild of a library, delete the corresponding .a file (or use make clean which will distclean the 3rd party libs).

To build: just type `make`.

### Mac OS X
Install prereqs for SDL via homebrew.
You likely also need GNU coreutils (e.g. gmkdir, ginstall, ...)

To build: just type `make`.

## Android
TBD

## Usage
Game resources belong in assets/.

