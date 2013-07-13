# Bloq
A cross-platform 2D top-down/platformer-style game engine. Licensed under LGPLv3.

## Building
### Linux
You need all of the prerequisites that SDL2 requires.
You also need a version of GCC with C++11 / C++0x support (gcc 4.7 works).

Libraries that are used by the engine are included in lib/ with a makefile to build all as static libraries which get placed in lib/build/...
The makefile is designed to avoid rebuilding a given library if the .a file exists. To force a rebuild of a library, delete the corresponding .a file (or use make clean which will distclean the 3rd party libs).

To build: just type `make`.

### Mac OS X
Install prereqs for SDL2 via homebrew.
You likely also need GNU coreutils (e.g. `gmkdir`, `ginstall`, ...)

You need a recent version of Xcode with the command-line tools package installed. (`clang++` will be used to build on OS X).

To build: just type `make`.

### Android
TBD

### iOS
TBD

## Usage
Game resources go in assets/.

## FAQ

### Building with gcc instead of clang on OS X?
It seems possible but you need to install a more modern GCC than Xcode provides. e.g. `brew tap homebrew/versions && brew install gcc48`. Then just change the `CXX` make variable appropriately when building.

### What are your motivations behind writing this, licensing with the LGPL, etc?
I wanted to write a game that runs on multiple platforms, but the cross platform toolkits and other methods that exist have one or more disadvantages:

* Bulky in terms of run-time support. If I'm writing a game that runs on mobile platforms, a simple 2D game shouldn't require a 20+ meg ipa/apk.
* Inflexible, or batteries not included. If the toolkit in question was even open source, it might not include higher-level "game" functionality beyond just input/graphics/etc primitives and I would have to write that myself anyway.
* Requirements that don't make sense. One system I looked at was free, but required some expensive commercial tool to produce an iOS app for some reason.
* Incomplete. Some of the projects out there show great promise but just aren't complete, or look like "hacky" solutions to run code on mobile targets.
* The build tools aren't great or are cumbersome to use. I wanted to work with tools I was already familiar with and be able to create/test the framework and game on a desktop platform (not running in the iOS/Android simulator for example).
* Having to write in an unfamiliar language/platform, like toolkits that require using JS/HTML5, etc.
* Brush up on my C/C++, especially the new C++11 stuff.

If you want to use it commercially you can (the license permits this, obviously). The goal was to make the engine once and then make it easy to drop in some assets and scripts to have a working game.