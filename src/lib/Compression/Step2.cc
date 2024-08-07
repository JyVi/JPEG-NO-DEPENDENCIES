#include "./Step2.hh"
#include <array>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Map.h>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <eigen3/Eigen/src/Core/util/Constants.h>
#include <iostream>
#include <memory>

std::shared_ptr<BlockMatrixtoQuant> allocateBlockMatrixtoquant(std::shared_ptr<Splitted> Splitted)
{
    // allocate a vector at the size NumberofChannels of shared ptr
    std::shared_ptr<BlockMatrixtoQuant> Matrixes = 
        std::make_shared<BlockMatrixtoQuant>((*Splitted).getNumberofChannels());

    for (int channel = 0; channel < (*Splitted).getNumberofChannels(); channel++)
    {
        // allocate a vector at the size BlockWidth * BlockHeight of unique ptr
        std::shared_ptr<std::vector<std::unique_ptr<std::array<short, 64>>>> chan = 
            std::make_shared<std::vector<std::unique_ptr<std::array<short, 64>>>>(
                (*Splitted).getBlockHeight() * (*Splitted).getBlockWidth());

        for (size_t i = 0; i < (*Splitted).getBlockHeight() * (*Splitted).getBlockWidth(); i++)
        {
            // allocate each 64 short array
            (*chan)[i] = std::make_unique<std::array<short, 64>>();
        }

        (*Matrixes)[channel] = chan;
    }

    return Matrixes;
}

std::shared_ptr<BlockMatrixtoQuant> DCTTransform::applyingDCT(std::shared_ptr<Splitted> Splitted)
{
    std::shared_ptr<BlockMatrixtoQuant> DCTApplied = allocateBlockMatrixtoquant(Splitted);
    
    // stack opti at least I suppose
    Eigen::Matrix<float, 8, 8, Eigen::RowMajor> MatrixResult(8,8);
    Eigen::Matrix<float, 8, 8, Eigen::RowMajor> MatrixProvider(8,8);
    Eigen::Matrix<float, 8, 8, Eigen::RowMajor> DCTResult(8,8);

    for (int channel = 0; channel < (*Splitted).getNumberofChannels(); channel++)
    {
        std::shared_ptr<std::vector<std::unique_ptr<std::array<short, 64>>>> chanReceiver = (*DCTApplied)[channel];
        std::shared_ptr<std::vector<std::unique_ptr<std::array<char, 64>>>> chanProvider = (*(*Splitted).getChannels())[channel];
        for (size_t i = 0; i < (*Splitted).getBlockHeight(); i++)
        {
            for (size_t j = 0; j < (*Splitted).getBlockWidth(); j++)
            {
                // moving every pointer to array to new pointer to do magic here (matrix multiplication)
                std::unique_ptr<std::array<short, 64>> BlockResult = std::move((*chanReceiver)[i * (*Splitted).getBlockHeight() + j]);
                std::unique_ptr<std::array<char, 64>> BlockProvider = std::move((*chanProvider)[i * (*Splitted).getBlockHeight() + j]);

                // TODO: Eigen multiplication here
                // will do: blockresult = round(DCTkernel * BlockProvider * DCTkernelTransposed)
                // either doing round to all the numbers
                // or 
                // just the fact of going from float to short should 
                // do the trick by truncating the data
                // be careful about it, weird behavior from float to standard 
                // byte data
                
                // a map is a view that traits data as an eigen object without making a copy
                Eigen::Map<Eigen::Matrix<char, 8,8, Eigen::RowMajor>> mapBlockProvider((*BlockProvider).data());

                MatrixProvider = mapBlockProvider.cast<float>();

                DCTResult = DCTTransform::DCTKernelMatrix * MatrixProvider * DCTTransform::DCTKernelMatrixTranspose;

                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        //std::cout << "k: " << k << "l: " << l << std::endl;
                        //std::cout << DCTResult(k, l) << std::endl;

                        // TODO: it is crashing because of the BlockMatrix init BlockWidth and Height taking the previous width and height of the image and not the block size
                        (*BlockResult)[k * 8 + l] = static_cast<short>(std::round(DCTResult(k, l)));
                    }
                }
                //std::cout << "block: " << i << " " << j << " " << i * j << std::endl;
                
                // moving back the data
                (*chanProvider)[i * (*Splitted).getBlockHeight() + j] = std::move(BlockProvider);
                (*chanReceiver)[i * (*Splitted).getBlockHeight() + j] = std::move(BlockResult);
            }
        }
    }

    return DCTApplied;
}
