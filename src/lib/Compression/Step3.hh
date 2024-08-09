#include "Step1.hh"
#include "Step2.hh"
#include <memory>

namespace Quantification {

    const std::array<short, 64> QuantMatrix =
    {
        16, 11, 10, 16, 24, 40, 51, 61, 
        12, 12, 14, 19, 26, 58, 60, 55, 
        14, 13, 16, 24, 40, 57, 69, 56, 
        14, 17, 22, 29, 51, 87, 80, 62, 
        18, 22, 37, 56, 68, 109, 103, 77, 
        24, 35, 55, 64, 81, 104, 113, 92, 
        49, 64, 76, 87, 103, 121, 120, 101, 
        72, 92, 95, 98, 112, 100, 103, 99
    };

    // default compression rate, which is 50 
    void QuantificationProcess(std::shared_ptr<BlockMatrixtoQuant> toQuant, 
                               std::shared_ptr<Splitted> splitted);

    /*
     * @brief move the toQuant pointer to free the memory, the uniques ptr
     * are moved for each channel of each blocks
     * */
    void QuantificationProcess(std::shared_ptr<BlockMatrixtoQuant> toQuant, 
                               int quantfactor,
                               std::shared_ptr<Splitted> splitted);
}

