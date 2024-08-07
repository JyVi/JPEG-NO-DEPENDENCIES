#pragma once
#include "./Step1.hh"
#include <memory>
#include <numbers>
#include <cmath>
#include <eigen3/Eigen/Dense>

typedef std::vector<std::shared_ptr<std::vector<std::unique_ptr<std::array<short, 64>>>>> BlockMatrixtoQuant;

std::shared_ptr<BlockMatrixtoQuant> allocateBlockMatrixtoquant(std::shared_ptr<Splitted> Splitted);

namespace DCTTransform {

    const float over2 = 1.0f * std::numbers::sqrt2_v<float>;
    const float piF = std::numbers::pi_v<float>;

    const Eigen::Matrix<float, 8, 8> DCTKernelMatrix = (Eigen::Matrix<float, 8, 8>() << 
        0.5f * over2, 0.5f * over2, 0.5f * over2, 0.5f * over2, 0.5f * over2, 0.5f * over2, 0.5f * over2, 0.5f * over2,
        0.5f * std::cos(piF / 16), 0.5f * std::cos(3 * piF / 16), 0.5f * std::cos(5 * piF / 16), 0.5f * std::cos(7 * piF / 16),
                        0.5f * std::cos(9 * piF / 16), 0.5f * std::cos(11 * piF / 16), 0.5f * std::cos(13 * piF / 16), 0.5f * std::cos(15 * piF / 16),

        0.5f * std::cos(piF / 8), 0.5f * std::cos(3 * piF / 8), 0.5f * std::cos(5 * piF / 8), 0.5f * std::cos(7 * piF / 8), 
                        0.5f * std::cos(9 * piF / 8), 0.5f * std::cos(11 * piF / 8), 0.5f * std::cos(13 * piF / 8), 0.5f * std::cos(15 * piF / 8),

        0.5f * std::cos(3 * piF / 16), 0.5f * std::cos(9 * piF / 16), 0.5f * std::cos(15 * piF / 16), 0.5f * std::cos(21 * piF / 16),
                        0.5f * std::cos(27 * piF / 16), 0.5f * std::cos(33 * piF / 16), 0.5f * std::cos(39 * piF / 16), 0.5f * std::cos(45 * piF / 16),

        0.5f * std::cos(piF / 4), 0.5f * std::cos(3 * piF / 4), 0.5f * std::cos(5 * piF / 4), 0.5f * std::cos(7 * piF / 4),
                        0.5f * std::cos(9 * piF / 4), 0.5f * std::cos(11 * piF / 4), 0.5f * std::cos(13 * piF / 4), 0.5f * std::cos(15 * piF / 4),

        0.5f * std::cos(5 * piF / 16), 0.5f * std::cos(15 * piF / 16), 0.5f * std::cos(25 * piF / 16), 0.5f * std::cos(35 * piF / 16),
                        0.5f * std::cos(45 * piF / 16), 0.5f * std::cos(55 * piF / 16), 0.5f * std::cos(65 * piF / 16), 0.5f * std::cos(75 * piF / 16),

        0.5f * std::cos(3 * piF / 8), 0.5f * std::cos(9 * piF / 8), 0.5f * std::cos(5 * piF / 4), 0.5f * std::cos(21 * piF / 8),
                        0.5f * std::cos(27 * piF / 8), 0.5f * std::cos(33 * piF / 8), 0.5f * std::cos(39 * piF / 8), 0.5f * std::cos(45 * piF / 8),

        0.5f * std::cos(7 * piF / 16), 0.5f * std::cos(21 * piF / 16), 0.5f * std::cos(35 * piF / 16), 0.5f * std::cos(49 * piF / 16),
                        0.5f * std::cos(63 * piF / 16), 0.5f * std::cos(77 * piF / 16), 0.5f * std::cos(91 * piF / 16), 0.5f * std::cos(105 * piF / 16)).finished();


    const Eigen::Matrix<float, 8, 8> DCTKernelMatrixTranspose = (Eigen::Matrix<float, 8, 8>() << 
        0.5f * over2, 0.5f * std::cos(piF / 16), 0.5f * std::cos(piF / 8), 0.5f * std::cos(3 * piF / 16), 
                        0.5f * std::cos(piF / 4), 0.5f * std::cos(5 * piF / 16), 0.5f * std::cos(3 * piF / 8), 0.5f * std::cos(7 * piF / 16), 
    
        0.5f * over2, 0.5f * std::cos(3 * piF / 16), 0.5f * std::cos(3 * piF / 8), 0.5f * std::cos(9 * piF / 16),
                        0.5f * std::cos(3 * piF / 4), 0.5f * std::cos(15 * piF / 16), 0.5f * std::cos(9 * piF / 8), 0.5f * std::cos(21 * piF / 16), 

        0.5f * over2, 0.5f * std::cos(5 * piF / 16), 0.5f * std::cos(5 * piF / 8), 0.5f * std::cos(15 * piF / 16),
                        0.5f * std::cos(5 * piF / 4), 0.5f * std::cos(25 * piF / 16), 0.5f * std::cos(5 * piF / 4), 0.5f * std::cos(35 * piF / 16), 

        0.5f * over2, 0.5f * std::cos(7 * piF / 16), 0.5f * std::cos(7 * piF / 8), 0.5f * std::cos(21 * piF / 16),
                        0.5f * std::cos(7 * piF / 4), 0.5f * std::cos(35 * piF / 16), 0.5f * std::cos(21 * piF / 8), 0.5f * std::cos(49 * piF / 16), 

        0.5f * over2, 0.5f * std::cos(9 * piF / 16), 0.5f * std::cos(9 * piF / 8), 0.5f * std::cos(27 * piF / 16),
                        0.5f * std::cos(9 * piF / 4), 0.5f * std::cos(45 * piF / 16), 0.5f * std::cos(27 * piF / 8), 0.5f * std::cos(63 * piF / 16), 

        0.5f * over2, 0.5f * std::cos(11 * piF / 16), 0.5f * std::cos(11 * piF / 8), 0.5f * std::cos(33 * piF / 16),
                        0.5f * std::cos(11 * piF / 4), 0.5f * std::cos(55 * piF / 16), 0.5f * std::cos(33 * piF / 8), 0.5f * std::cos(77 * piF / 16), 

        0.5f * over2, 0.5f * std::cos(13 * piF / 16), 0.5f * std::cos(13 * piF / 8), 0.5f * std::cos(39 * piF / 16), 
                        0.5f * std::cos(13 * piF / 4), 0.5f * std::cos(65 * piF / 16), 0.5f * std::cos(39 * piF / 8), 0.5f * std::cos(91 * piF / 16), 

        0.5f * over2, 0.5f * std::cos(15 * piF / 16), 0.5f * std::cos(15 * piF / 8), 0.5f * std::cos(45 * piF / 16), 
                        0.5f * std::cos(15 * piF / 4), 0.5f * std::cos(75 * piF / 16), 0.5f * std::cos(45 * piF / 8), 0.5f * std::cos(105 * piF / 16)).finished();


    std::shared_ptr<BlockMatrixtoQuant> applyingDCT(std::shared_ptr<Splitted> Splitted);

} // DCTTransform
