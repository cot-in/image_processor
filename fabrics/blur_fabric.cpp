#include "blur_fabric.h"
#include "../exceptions.h"
#include "../filters/blur.h"

std::shared_ptr<BaseFilter> BlurFabric::Create(const std::vector<std::string> &input_params) {
    if (input_params.empty()) {
        throw BlurFabricException("too few parameters (1 expected)");
    } else if (input_params.size() > 1) {
        throw BlurFabricException("too many parameters (1 expected)");
    }
    try {
        double sigma = std::stod(input_params[0]);
        if (sigma == 0) {
            throw BlurFabricException("sigma should be positive");
        }
        return std::make_shared<Blur>(sigma);
    } catch (BlurFabricException &e) {
        throw e;
    } catch (...) {
        throw BlurFabricException("wrong filter parameter");
    }
}
