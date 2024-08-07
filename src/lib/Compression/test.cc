#include "../DataStructure/ImageEssential.hxx"
#include "Step1.hh"
#include "Step2.hh"
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <numbers>
#include <eigen3/Eigen/Dense>

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
    std::cout << "program started\n" << "\n" << std::endl;
    if (argc >= 2)
        std::cout << argv[1] << std::endl;
    else
        return 1;

    std::cout << std::numbers::pi << std::endl;
    std::cout << std::numbers::sqrt2_v<float> << std::endl;
    std::cout << 1.0f/2.0f * std::numbers::sqrt2_v<float> << std::endl;

    float floaty = 1.0f/2.0f * std::numbers::sqrt2_v<float>;
    Uint8 charry = 255;
    Uint8 charry1 = 127;
    Uint8 charry2 = 128;
    Uint8 charry3 = 200;
    Uint8 charry4 = 200 - 128;
    Uint8 charry5 = 40 - 128;

    std::cout << floaty << std::endl;
    std::cout << charry  << " " << charry1 << " " << charry2 << " " << charry3 << " " << charry4 << " " << charry5 << std::endl;

    std::cout << "image not loaded" << std::endl;
    SDL_Surface *surf = IMG_Load(argv[1]);
    std::cout << "image loaded" << std::endl;

    SDL_PixelFormat *format = &surf->format;
    const SDL_PixelFormatDetails* details = SDL_GetPixelFormatDetails(*format);

    printPixelFormatDetails(details);

    std::shared_ptr<std::vector<Uint8>> pix = 
        std::make_shared<std::vector<Uint8>>
            (static_cast<Uint8*>(surf->pixels),
             static_cast<Uint8*>(surf->pixels) + surf->h * surf->w * 3);

    ImageEssential<Uint8> essence = ImageEssential<Uint8>(surf->w * 3, surf->h,
                                                          surf->format, 
                                                          std::move(pix));

    std::cout << "essential image" << std::endl;

    /*
    std::array<char, 64> charArray = {0, 1, 2, 3, 4, 5, 6, 7,
                                      8, 9, 10, 11, 12, 13, 14, 15,
                                      16, 17, 18, 19, 20, 21, 22, 23,
                                      24, 25, 26, 27, 28, 29, 30, 31,
                                      32, 33, 34, 35, 36, 37, 38, 39,
                                      40, 41, 42, 43, 44, 45, 46, 47,
                                      48, 49, 50, 51, 52, 53, 54, 55,
                                      56, 57, 58, 59, 60, 61, 62, 63};

    Eigen::Map<Eigen::Matrix<char, 8, 8>> mapCharArray(charArray.data());

    std::cout << mapCharArray << std::endl;

    Eigen::Matrix<float, 8, 8> matrixFromMap = mapCharArray.cast<float>();

    std::cout << matrixFromMap << std::endl;
    matrixFromMap(0,0) = 1.4f;
    std::cout << matrixFromMap(0,0) << std::endl;
    */
    std::shared_ptr<Splitted> testySplit = std::make_shared<Splitted>();
    std::shared_ptr<BlockMatrix> vec = channelSplitting(essence.getPixels(), essence.getWidth(), essence.getHeight(), 3, 3);
    std::cout << "channels splitted" << std::endl;
    testySplit.get()->setChannels(vec, essence.getWidth(), essence.getHeight(), 3);

    std::shared_ptr<BlockMatrixtoQuant> ToQuant = DCTTransform::applyingDCT(testySplit);

    SDL_DestroySurface(surf);

    return 0;
}
