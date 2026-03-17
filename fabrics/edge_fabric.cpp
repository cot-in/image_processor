#include "edge_fabric.h"
#include "../exceptions.h"
#include "../filters/edge_filter.h"

std::shared_ptr<BaseFilter> EdgeDetectionFabric::Create(const std::vector<std::string> &input_params) {
    if (input_params.empty()) {
        throw EdgeDetectionFabricException("too few parameters (1 expected)");
    } else if (input_params.size() > 1) {
        throw EdgeDetectionFabricException("too many parameters (1 expected)");
    }
    try {
        double threshold = std::stod(input_params[0]);
        return std::make_shared<EdgeDetection>(threshold);
    } catch (...) {
        throw EdgeDetectionFabricException("wrong filter parameter");
    }
}
