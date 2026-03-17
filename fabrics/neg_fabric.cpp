#include "neg_fabric.h"
#include "../exceptions.h"
#include "../filters/neg.h"

std::shared_ptr<BaseFilter> NegativeFabric::Create(const std::vector<std::string> &input_params) {
    if (!input_params.empty()) {
        throw NegativeFabricException("the filter does not require any parameters for itself");
    }
    return std::make_shared<Negative>();
}
