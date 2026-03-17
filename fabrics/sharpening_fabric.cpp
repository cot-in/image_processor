#include "sharpening_fabric.h"
#include "../exceptions.h"
#include "../filters/sharpening.h"

std::shared_ptr<BaseFilter> SharpeningFabric::Create(const std::vector<std::string> &input_params) {
    if (!input_params.empty()) {
        throw SharpeningFabricException("the filter does not require any parameters for itself");
    }
    return std::make_shared<Sharpening>();
}
