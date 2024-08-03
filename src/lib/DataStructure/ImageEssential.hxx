#pragma once
//#include "./DataStructure.hh"
#include <SDL3/SDL_pixels.h>
#include <memory>
#include <vector>


/*
 * @class ImageEssential
 *
 * @brief First abstraction of an Image by stocking its pixel matrix 
 * to compress and decrompress it later
 * */
template<typename T>
class ImageEssential
{
    public:
        ImageEssential(int w, int h, SDL_PixelFormat format, std::shared_ptr<std::vector<T>> pixels);
        int getWidth();
        int getHeight();

        void setWidth();
        void setHeight();

        SDL_PixelFormat getPixelFormat();
        void setPixelFormat();
        /* Is not a typical getter, data may be modified */
        std::shared_ptr<std::vector<T>> getPixels();
        
    private:
        int width;
        int height;
        /* SDL enum is used for compbatibilities reason */
        SDL_PixelFormat format;
        /* the actual pixel matrix*/
        std::shared_ptr<std::vector<T>> pixels;
};


// TODO: what to do when size is 24 or is a float
template<typename T>
std::shared_ptr<std::vector<T>> getPixelVector(void *surfaceArray,
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
