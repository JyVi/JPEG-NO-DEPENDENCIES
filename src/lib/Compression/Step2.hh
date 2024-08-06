#pragma once
#include "../DataStructure/ImageEssential.hxx"
#include <numbers>
#include <cmath>
#include <array>

const float over2 = 1.0f * std::numbers::sqrt2_v<float>;
const float piF = std::numbers::pi_v<float>;

const std::array<float, 64> DCTKernelMatrix = { 
    over2, over2, over2, over2, over2, over2, over2, over2,
    std::cos(piF / 16), std::cos(3 * piF / 16), std::cos(5 * piF / 16), std::cos(7 * piF / 16),
                        std::cos(9 * piF / 16), std::cos(11 * piF / 16), std::cos(13 * piF / 16), std::cos(15 * piF / 16), 

    std::cos(piF / 8), std::cos(3 * piF / 8), std::cos(5 * piF / 8), std::cos(7 * piF / 8), 
                        std::cos(9 * piF / 8), std::cos(11 * piF / 8), std::cos(13 * piF / 8), std::cos(15 * piF / 8), 

    std::cos(3 * piF / 16), std::cos(9 * piF / 16), std::cos(15 * piF / 16), std::cos(21 * piF / 16),
                        std::cos(27 * piF / 16), std::cos(33 * piF / 16), std::cos(39 * piF / 16), std::cos(45 * piF / 16), 

    std::cos(piF / 4), std::cos(3 * piF / 4), std::cos(5 * piF / 4), std::cos(7 * piF / 4),
                        std::cos(9 * piF / 4), std::cos(11 * piF / 4), std::cos(13 * piF / 4), std::cos(15 * piF / 4), 

    std::cos(5 * piF / 16), std::cos(15 * piF / 16), std::cos(25 * piF / 16), std::cos(35 * piF / 16),
                        std::cos(45 * piF / 16), std::cos(55 * piF / 16), std::cos(65 * piF / 16), std::cos(75 * piF / 16), 

    std::cos(3 * piF / 8), std::cos(9 * piF / 8), std::cos(5 * piF / 4), std::cos(21 * piF / 8),
                        std::cos(27 * piF / 8), std::cos(33 * piF / 8), std::cos(39 * piF / 8), std::cos(45 * piF / 8), 

    std::cos(7 * piF / 16), std::cos(21 * piF / 16), std::cos(35 * piF / 16), std::cos(49 * piF / 16),
                        std::cos(63 * piF / 16), std::cos(77 * piF / 16), std::cos(91 * piF / 16), std::cos(105 * piF / 16)
};


const std::array<float, 64> DCTKernelMatrixTranspose = {
    over2, std::cos(piF / 16),     std::cos(piF / 8),    std::cos(3 * piF / 16), std::cos(piF / 4), std::cos(5 * piF / 16), std::cos(3 * piF / 8), std::cos(7 * piF / 16), 
    over2, std::cos(3 * piF / 16), std::cos(3 * piF / 8), std::cos(9 * piF / 16), std::cos(3 * piF / 4), std::cos(15 * piF / 16), std::cos(9 * piF / 8), std::cos(21 * piF / 16), 
    over2, std::cos(5 * piF / 16), std::cos(5 * piF / 8), std::cos(15 * piF / 16), std::cos(5 * piF / 4), std::cos(25 * piF / 16), std::cos(5 * piF / 4), std::cos(35 * piF / 16), 
    over2, std::cos(7 * piF / 16), std::cos(7 * piF / 8), std::cos(21 * piF / 16), std::cos(7 * piF / 4), std::cos(35 * piF / 16), std::cos(21 * piF / 8), std::cos(49 * piF / 16), 
    over2, std::cos(9 * piF / 16), std::cos(9 * piF / 8), std::cos(27 * piF / 16), std::cos(9 * piF / 4), std::cos(45 * piF / 16), std::cos(27 * piF / 8), std::cos(63 * piF / 16), 
    over2, std::cos(11 * piF / 16), std::cos(11 * piF / 8), std::cos(33 * piF / 16), std::cos(11 * piF / 4), std::cos(55 * piF / 16), std::cos(33 * piF / 8), std::cos(77 * piF / 16), 
    over2, std::cos(13 * piF / 16), std::cos(13 * piF / 8), std::cos(39 * piF / 16), std::cos(13 * piF / 4), std::cos(65 * piF / 16), std::cos(39 * piF / 8), std::cos(91 * piF / 16), 
    over2, std::cos(15 * piF / 16), std::cos(15 * piF / 8), std::cos(45 * piF / 16), std::cos(15 * piF / 4), std::cos(75 * piF / 16), std::cos(45 * piF / 8), std::cos(105 * piF / 16)
};
