#pragma once
#include "../DataStructure/ImageEssential.hxx"
#include <cassert>
#include <utility>
#include <array>
#include <vector>
#include <memory>

typedef std::vector<std::shared_ptr<std::vector<std::unique_ptr<std::array<Uint8, 64>>>>> BlockMatrix;
// Type alias for the function pointer
template<typename T>
using ValueFunction = Uint8(*)(int offset, int channel, size_t i, size_t j, size_t k, size_t n, int w, std::shared_ptr<std::vector<T>> vec);

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

/*
 * TODO replace this to be a function pointer so its lighter on cpu without 
 * testing offset every time, only once, 
 * if (offset != 0)
 *      funptr* = vec[(i * 8 + k) * w + (j * 8 + n * offset + channel)]
 * else
 *      // no offset 
 *      funptr* = (vec[(i * 8 + k) * w + (j * 8 + n)] >> 8 * channel) & 0xff
 * */
template<typename T>
Uint8 determineValueWithOffset(int offset, int channel, size_t i, 
                               size_t j, size_t k, size_t n, int w, 
                               std::shared_ptr<std::vector<T>> vec)
{
    if (offset != 0)
        return (*vec)[(i + k) * w + (j + n * offset + channel)];
    size_t position = (i + k) * w + (j + n);
    assert(position < vec->size() && "Out of bound");
    return ((*vec)[position] >> 8 * channel) & 0xff;
}

template<typename T>
Uint8 determineValueWithoutOffset(int offset, int channel, size_t i, 
                                  size_t j, size_t k, size_t n, int w, 
                                  std::shared_ptr<std::vector<T>> vec)
{
    size_t position = (i + k) * w + (j + n);
    assert(position < vec->size() && "Out of bound withoutOffset");
    return ((*vec)[position] >> 8 * channel) & 0xff;
}

template<typename T>
ValueFunction<T> getFunctionPtr(int offset)
{
    if (offset != 0)
        return &determineValueWithOffset<T>;
    return &determineValueWithoutOffset<T>;
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
