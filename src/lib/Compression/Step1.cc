#include "./Step1.hh"
#include <memory>

Splitted::Splitted() {}
Splitted::~Splitted() {}

void Splitted::setChannels(std::shared_ptr<BlockMatrix> vec, int width, 
                           int height, int numberOfchannels, int offset)
{
    int blockWidth;
    if (offset == 0)
        blockWidth = width / 8 + (width % 8 == 0 ? 0 : 1);
    else
        blockWidth = (width / numberOfchannels) / 8 + 
            ((width / numberOfchannels) % 8 == 0 ? 0: 1);

    this->setBlockWidth(blockWidth);
    this->setBlockHeight(height / 8 + (height % 8 == 0 ? 0 : 1));
    this->setNumberofChannels(numberOfchannels);
    this->channels = std::move(vec);
}

void Splitted::setNumberofChannels(int numberOfchannels)
{
    this->numberofChannels = numberOfchannels;
}

void Splitted::setBlockWidth(int width)
{
    this->blockWidth = width;
}

void Splitted::setBlockHeight(int height)
{
    this->blockHeight = height;
}


std::shared_ptr<BlockMatrix> Splitted::getChannels()
{
    return this->channels;
}

int Splitted::getBlockWidth()
{
    return this->blockWidth;
}

int Splitted::getBlockHeight()
{
    return this->blockHeight;
}

int Splitted::getNumberofChannels()
{
    return this->numberofChannels;
}
