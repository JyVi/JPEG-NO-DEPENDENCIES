#include "Step3.hh"
#include "Step1.hh"
#include <memory>
#include <utility>

// I am freeing the short array uniq ptr I don't need its data anymore
void BlockQuantization(std::unique_ptr<std::array<short, 64>> QuantProvider, 
                       short alpha,
                       std::unique_ptr<std::array<char, 64>>& QuantReceiver)
{
    // TODO: opti by doing the matrix calcul once and then save it 
    // create a matrix of this QuantProvider->at(i) / (alpha * Quantification::QuantMatrix[i] + 50) / 100;
    // to pass in argument 
    for (int i = 0; i < 64; i++)
    {
        QuantReceiver->at(i) = QuantProvider->at(i) / ((alpha * Quantification::QuantMatrix[i] + 50) / 100);
    }
}

void Quantification::QuantificationProcess(
    std::shared_ptr<BlockMatrixtoQuant> toQuant, int quantfactor,
    std::shared_ptr<Splitted> splitted)
{
    short alpha;
    if (quantfactor < 50)
        alpha = 5000 / quantfactor;
    else
        alpha = 200 - 2 * quantfactor;

    for (int channel = 0; channel < splitted->getNumberofChannels(); channel++)
    {
        std::shared_ptr<std::vector<std::unique_ptr<std::array<short, 64>>>> channelMatrixDCT = (*toQuant)[channel];
        std::shared_ptr<std::vector<std::unique_ptr<std::array<char, 64>>>> channelMatrixReceiver = splitted->getChannels()->at(channel);
        for (size_t k = 0; k < channelMatrixDCT->size(); k++)
        {
            BlockQuantization(std::move(channelMatrixDCT->at(k)), alpha, channelMatrixReceiver->at(k));
        }
    }
}

void Quantification::QuantificationProcess(
    std::shared_ptr<BlockMatrixtoQuant> toQuant, 
    std::shared_ptr<Splitted> splitted)
{
    Quantification::QuantificationProcess(std::move(toQuant), 50,
                                          std::move(splitted));
}
