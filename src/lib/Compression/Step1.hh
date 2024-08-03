#pragma once
#include "../DataStructure/ImageEssential.hxx"
#include <iostream>
#include <cassert>
#include <utility>
#include <array>
#include <vector>
#include <memory>

typedef std::vector<std::shared_ptr<std::vector<std::unique_ptr<std::array<Uint8, 64>>>>> BlockMatrix;

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
Uint8 determineValue(int offset, int channel, size_t i, size_t j, 
                       size_t k, size_t n, int w, std::shared_ptr<std::vector<T>> vec)
{
    if (offset != 0)
        return (*vec)[(i + k) * w + (j + n * offset + channel)];
    assert((i + k) * w + (j + n) < vec->size() && "Out of bound");
    return ((*vec)[(i + k) * w + (j + n)] >> 8 * channel) & 0xff;
}

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

    for (int chan = 0; chan < numberOfChannels; chan++)
    {
        (*channels)[chan] = std::make_shared<std::vector<std::unique_ptr<std::array<Uint8, 64>>>>();
        std::shared_ptr<std::vector<std::unique_ptr<std::array<Uint8, 64>>>> channel = (*channels)[chan];

        size_t cpt = 0;
        // TODO: do not forget about the padding

        for (size_t i = 0; i < h; i += 8)
        {
            for (size_t j = 0; j < w; j += 8 * delta)
            {
                // blocking splitting
                std::unique_ptr<std::array<Uint8, 64>> block = std::make_unique<std::array<Uint8, 64>>();
                for (size_t k = 0; k < 8; k++)
                {
                    // i * 8 + k, j * 8 + n: take into account the i,j += 8
                    for (size_t n = 0; n < 8; n++)
                    {
                        (*block)[k * 8 + n] = determineValue(offset, chan, i, j, k, n, w, vec);
                    }
                }
                channel->push_back(std::move(block));
            }
        }
    }
    return channels;
}
