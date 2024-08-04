#include "./Step1.hh"
#include <memory>

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

