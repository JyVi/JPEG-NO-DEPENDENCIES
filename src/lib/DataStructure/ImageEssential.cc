#include "ImageEssential.hxx"
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <vector>

// TODO: what to do when size is 24 or is a float
template<typename T>
std::shared_ptr<std::vector<T>> getPixelVector2(void *surfaceArray,
                                               SDL_PixelFormat format,
                                               size_t size)
{
    const SDL_PixelFormatDetails* details = SDL_GetPixelFormatDetails(format);
    switch (details->bits_per_pixel) {
        case 64:
            return std::make_shared<std::vector<Uint64>>
            (static_cast<Uint64*>(surfaceArray),
             static_cast<Uint64*>(surfaceArray) + size);
        case 32:
            return std::make_shared<std::vector<Uint64>>
            (static_cast<Uint32*>(surfaceArray),
             static_cast<Uint32*>(surfaceArray) + size);
        case 16:
            return std::make_shared<std::vector<Uint64>>
            (static_cast<Uint16*>(surfaceArray),
             static_cast<Uint16*>(surfaceArray) + size);
        case 8:
            return std::make_shared<std::vector<Uint64>>
            (static_cast<Uint8*>(surfaceArray),
             static_cast<Uint8*>(surfaceArray) + size);
        default:
            return std::make_shared<std::vector<Uint64>>
            (static_cast<Uint64*>(surfaceArray),
             static_cast<Uint64*>(surfaceArray) + size);
    }
}

/*
template<typename T>
ImageEssential<T>::ImageEssential(int w, 
                                  int h, 
                                  SDL_PixelFormat format,
                                  std::shared_ptr<std::vector<T>> pixels)
{
    this->width = w;
    this->height = h;
    this->format = format;
    this->pixels = pixels;
}

template<typename T>
int ImageEssential<T>::getWidth()
{
    return this->width;
}

template<typename T>
int ImageEssential<T>::getHeight()
{
    return this->height;
}

template<typename T>
std::shared_ptr<std::vector<T>> ImageEssential<T>::getPixels()
{
    return this->pixels;
}
*/
