#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <memory>

/*
 * @class
 *
 * @brief: the class is a wrapper to sdl surface I am trying it to be optimized
 * for my used case which is compression
 * This is an entry point but not the final class, an other class will be 
 * holding relevent information
 * */
class WrapperImage 
{
    public:
        WrapperImage();
        WrapperImage(SDL_Surface *surface);
        WrapperImage(std::string ImageToLoad);
        std::shared_ptr<SDL_Surface> getSurface();
    private:
        std::shared_ptr<SDL_Surface> SurfaceShared;
};
