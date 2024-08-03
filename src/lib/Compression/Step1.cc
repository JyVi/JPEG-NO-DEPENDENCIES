#include "./Step1.hh"
#include <array>
#include <memory>
#include <vector>

Splitted::Splitted() {}
Splitted::~Splitted() {}

void Splitted::setChannels(std::shared_ptr<BlockMatrix> vec)
{
    this->channels = std::move(vec);
}

std::shared_ptr<BlockMatrix> Splitted::getChannels()
{
    return this->channels;
}

/*
 * TODO replace this to be a function pointer so its lighter on cpu without 
 * testing offset every time, only once, 
 * if (offset != 0)
 *      funptr* = vec[(i * 8 + k) * w + (j * 8 + n * offset + channel)]
 * else
 *      // no offset 
 *      funptr* = (vec[(i * 8 + k) * w + (j * 8 + n)] >> 8 * channel) & 0xff
 * */
/*
template<typename T>
Uint8 determineValue(int offset, int channel, size_t i, size_t j, 
                       size_t k, size_t n, int w, std::shared_ptr<std::vector<T>> vec)
{
    if (offset != 0)
        return vec[(i * 8 + k) * w + (j * 8 + n * offset + channel)];
    return (vec[(i * 8 + k) * w + (j * 8 + n)] >> 8 * channel) & 0xff;
}
*/
/*
 * @brief split by the number of the image channels in 8x8 group
 *
 * @param offset: what is the number of bytes in a pixel and if is a power of 2
 * rtfm the readme(TODO), right now the white paper
 * */
/*
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
    
    for (int chan = 0; chan < numberOfChannels; chan++)
    {
        std::shared_ptr<std::vector<std::unique_ptr<std::array<Uint8, 64>>>> channel = (*channels)[chan];

        // TODO: take into account from the offset if it is bitmasking or iterating
        // over the array
        // TODO: do not forget about the padding

        for (size_t i = 0; i < h; i += 8)
        {
            for (size_t j = 0; j < w; j += 8)
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
                channel->emplace_back(block);
            }
        }
    }
    return channels;
}
*/
