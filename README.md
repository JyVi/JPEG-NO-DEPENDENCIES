# JPEG-NO-DEPENDENCIES
I am recreating the JPEG algorithm using C++, my build system for this project will be CMake using Clangd.

This project is part of a continuity of my current study courses.
I took in my school an "Électif", which are small side courses to direct us into choosing a suitable specialty for the next 2 years in EPITA Engineer cycle (ING2 and ING3).

I am experimenting with the CMake build system, which I used to build my projects during the C++ Piscine.
I will try to keep a clean build and structure for it.

I am going to try to rush it in 1 or 2 week (I hope so)




InstallDependencies.sh is an executable file for installing the relative 
dependencies of the project, especially the SDL2 dependencies and cmake


to append when trying to compile for SDL3 rather than SDL2
$(pkg-config --cflags sdl3) $(pkg-config --libs sdl3)


Thanks to the SDL discord from orlac and empyreanx
