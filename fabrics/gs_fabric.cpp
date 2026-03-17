#include "gs_fabric.h"
#include "../exceptions.h"
#include "../filters/gs.h"

std::shared_ptr<BaseFilter> GrayScaleFabric::Create(const std::vector<std::string> &input_params) {
    if (!input_params.empty()) {
        throw GrayScaleFabricException("the filter does not require any parameters for itself");
    }
    return std::make_shared<GrayScale>();
}
