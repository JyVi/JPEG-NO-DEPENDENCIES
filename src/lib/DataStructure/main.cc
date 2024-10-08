#include "ImageEssential.hxx"
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <memory>
#include <ostream>

void printPixelFormatDetails(const SDL_PixelFormatDetails* details) {
    std::cout << "SDL_PixelFormatDetails:\n"
              << "  format: " << details->format << "\n"
              << "  bits_per_pixel: " << static_cast<int>(details->bits_per_pixel) << "\n"
              << "  bytes_per_pixel: " << static_cast<int>(details->bytes_per_pixel) << "\n"
              << "  Rmask: " << details->Rmask << "\n"
              << "  Gmask: " << details->Gmask << "\n"
              << "  Bmask: " << details->Bmask << "\n"
              << "  Amask: " << details->Amask << "\n"
              << "  Rbits: " << static_cast<int>(details->Rbits) << "\n"
              << "  Gbits: " << static_cast<int>(details->Gbits) << "\n"
              << "  Bbits: " << static_cast<int>(details->Bbits) << "\n"
              << "  Abits: " << static_cast<int>(details->Abits) << "\n"
              << "  Rshift: " << static_cast<int>(details->Rshift) << "\n"
              << "  Gshift: " << static_cast<int>(details->Gshift) << "\n"
              << "  Bshift: " << static_cast<int>(details->Bshift) << "\n"
              << "  Ashift: " << static_cast<int>(details->Ashift) << "\n"
              << std::endl;
}

int main(int argc, char** argv)
{
    if (argc >= 2)
        std::cout << argv[1] << std::endl;
    else
     return 1;

    SDL_Surface *surf = IMG_Load(argv[1]);
    SDL_PixelFormat *format = &surf->format;

    const SDL_PixelFormatDetails* details = SDL_GetPixelFormatDetails(*format);

    printPixelFormatDetails(details);

    std::shared_ptr<std::vector<Uint8>> pix = 
        std::make_shared<std::vector<Uint8>>
            (static_cast<Uint8*>(surf->pixels),
             static_cast<Uint8*>(surf->pixels) + surf->h * surf->w*3);

    ImageEssential<Uint8> ImageEssential(surf->w, surf->h, surf->format, pix);

    SDL_DestroySurface(surf);


    return 0;
}
