#pragma once
#include "./DataStructure.hh"
#include <SDL3/SDL_pixels.h>
#include <memory>
#include <string>
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
        ImageEssential(std::string ImageName);
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
        SDL_PixelFormat format;
        /* the actual pixel matrix*/
        std::shared_ptr<std::vector<T>> Pixels;
};
