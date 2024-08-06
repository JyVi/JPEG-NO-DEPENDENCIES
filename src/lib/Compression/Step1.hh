#pragma once
#include "../DataStructure/ImageEssential.hxx"
#include <cassert>
#include <utility>
#include <array>
#include <vector>
#include <memory>

// type defintion for the container of the splitted 8x8 block matrix
typedef std::vector<std::shared_ptr<std::vector<std::unique_ptr<std::array<Uint8, 64>>>>> BlockMatrix;
// Type alias for the function pointer
template<typename T>
using ValueFunction = Uint8(*)(int offset, int channel, size_t i, size_t j, int k, int n, int w, std::shared_ptr<std::vector<T>> vec);

class Splitted
{
    public:
        Splitted();
        ~Splitted();
        void setChannels(std::shared_ptr<BlockMatrix> vec);
        std::shared_ptr<BlockMatrix> getChannels();
    private:
        std::shared_ptr<BlockMatrix> channels;
};

template<typename T>
Uint8 determineValueWithOffset(int offset, int channel, size_t i, 
                               size_t j, int k, int n, int w, 
                               std::shared_ptr<std::vector<T>> vec)
{
    size_t position = (i + k) * w + (j + n * offset + channel);
    assert(position < vec->size() && "Out of bound with offset");
    return (*vec)[position];
}

template<typename T>
Uint8 determineValueWithoutOffset(int offset, int channel, size_t i, 
                                  size_t j, int k, int n, int w, 
                                  std::shared_ptr<std::vector<T>> vec)
{
    size_t position = (i + k) * w + (j + n);
    assert(position < vec->size() && "Out of bound without offset");
    return ((*vec)[position] >> 8 * channel) & 0xff;
}

template<typename T>
ValueFunction<T> getFunctionPtr(int offset)
{
    if (offset != 0)
        return &determineValueWithOffset<T>;
    return &determineValueWithoutOffset<T>;
}

template<typename T>
std::unique_ptr<std::array<Uint8, 64>> blockwidthPadding(int offset, 
                                                         int channel, 
                                                         size_t i,
                                                         int deltaW,
                                                         size_t w,
                                                         std::shared_ptr<std::vector<T>> vec,
                                                         ValueFunction<T> determineValue)
{
    std:: unique_ptr<std::array<Uint8, 64>> block = 
        std::make_unique<std::array<Uint8, 64>>();
    for (int k = 0; k < 8; k++)
    {
        for (int l = 0; l < deltaW; l++)
            (*block)[k * 8 + l] = determineValue(offset, channel, i, w, k, l, w, vec);
        for (int m = 0; m < 8 - deltaW; m++)
            (*block)[k * 8 + m + deltaW] = determineValue(offset, channel, i, w, k, i - m, w, vec);
    }
    return block;
}

/*
 * (h - 8 - 1) for the last row block 
 * (j) because i am doing every columns
 * (k) for the non impacted rows 
 * (deltaH - m + 1) because I want to access the mirrored row 
 * */
template<typename T>
void blockHeightPadding(int offset, int channel, int deltaH, size_t h,
                        size_t w, std::shared_ptr<std::vector<T>> vec,
                        ValueFunction<T> determineValue, 
                        std::shared_ptr<std::vector<std::unique_ptr<std::array<Uint8, 64>>>> channelVector)
{
    for (size_t j = 0; j < w; j++)
    {
        std::unique_ptr<std::array<Uint8, 64>> block = 
            std::make_unique<std::array<Uint8, 64>>();
        for (int k = 0; k < deltaH; k++)
        {
            for (int l = 0; l < 8; l++)
                (*block)[k * 8 + l] = determineValue(offset, channel, h - 9, j, k, l, w, vec);
        }
        for (int m = deltaH; m < 8; m++)
        {
            for (int n = 0; n < 8; n++)
                (*block)[m * 8 + n] = determineValue(offset, channel, h - 9, j, deltaH - m + 1, n, w, vec);
        }
        channelVector->push_back(std::move(block));
    }
}

/*
 * @brief split by the number of the image channels in 8x8 group
 *
 * @param offset: what is the number of bytes in a pixel and if is a power of 2
 * rtfm the readme(TODO), right now the white paper
 * */
template<typename T>
std::shared_ptr<BlockMatrix> channelSplitting(
    std::shared_ptr<std::vector<T>> vec,
    int w,
    int h,
    int offset,
    int numberOfChannels)

{
    std::shared_ptr<BlockMatrix> channels = 
        std::make_shared<BlockMatrix>(numberOfChannels);
    
    size_t delta = 0;
    offset == 0 ? delta = 1 : delta = numberOfChannels;

    size_t padWidth = w % 8;
    size_t padHeight = h % 8;

    ValueFunction<T> determineValue = getFunctionPtr<T>(offset);

    for (int chan = 0; chan < numberOfChannels; chan++)
    {
        (*channels)[chan] = std::make_shared<std::vector<std::unique_ptr<std::array<Uint8, 64>>>>();
        std::shared_ptr<std::vector<std::unique_ptr<std::array<Uint8, 64>>>> channel = (*channels)[chan];

        size_t cpt = 0;
        // TODO: do not forget about the padding
        // maybe h - padwidth ? 
        for (size_t i = 0; i < h - padHeight; i += 8)
        {
            for (size_t j = 0; j < w - padWidth; j += 8 * delta)
            {
                // blocking splitting
                std::unique_ptr<std::array<Uint8, 64>> block = std::make_unique<std::array<Uint8, 64>>();
                for (size_t k = 0; k < 8; k++)
                {
                    // i * 8 + k, j * 8 + n: take into account the i,j += 8
                    for (size_t n = 0; n < 8; n++)
                    {
                        (*block)[k * 8 + n] = determineValue(offset, chan, i,
                                                             j, k, n, w, vec);
                    }
                }
                channel->push_back(std::move(block));
            }
            // block padding
            if (padWidth != 0)
            {
                std::unique_ptr<std::array<Uint8, 64>> block = 
                    blockwidthPadding(offset, chan, i, padWidth, w, vec,
                                      determineValue);
                channel->push_back(std::move(block));
            }
        }
        if (padHeight != 0)
            blockHeightPadding(offset, chan, padHeight, h, w, vec, 
                               determineValue, channel);
    }
    return channels;
}

