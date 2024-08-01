//#include "ImageEssential.hh"
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <ostream>

int main(int argc, char** argv)
{
    if (argc >= 2)
        std::cout << argv[1] << std::endl;
    //ImageEssential myEssential = ImageEssential(argv[1]);
    SDL_Surface *surf = IMG_Load(argv[1]);
    std::cout << surf->format << std::endl;
    SDL_PixelFormat *format = &surf->format;
    std::cout << *format << std::endl;
    std::cout << format << std::endl;
    SDL_DestroySurface(surf);

    return 0;
}
