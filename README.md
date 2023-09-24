# Yaytracer
Yay! A simple raytracer in C++ made for fun.

## Setup
All commands listed here should be run from the repository's root directory
unless otherwise specified.

### Prerequisites
* [Git][git]
* [CMake 3.23.0 or later][cmake]
* Some C++ build environment, such as GCC and Make or MSVC.

### Building
After cloning the repository, the submodules must be initialized once by
running:

    git submodule update --init
    
After this, and whenever the CMake files have been edited, run:
    
    cmake -B "./build"

This generates the files needed for your build environment to compile the
project as normal. You can also compile using the following command:

    cmake --build "./build"

## Running
The location of the generated executable `yaytracer` currently depends on your
build environment, but it will be somewhere in the `build` folder.

[git]:   <https://git-scm.com/>
[cmake]: <https://cmake.org/>
