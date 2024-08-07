#include "./Step1.hh"
#include <memory>

Splitted::Splitted() {}
Splitted::~Splitted() {}

void Splitted::setChannels(std::shared_ptr<BlockMatrix> vec, int width, 
                           int height, int numberOfchannels)
{
    this->setBlockWidth(width);
    this->setBlockHeight(height);
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
