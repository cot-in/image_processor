#include "crop_fabric.h"
#include "../exceptions.h"
#include "../filters/crop.h"
#include <charconv>

std::shared_ptr<BaseFilter> CropFabric::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() < 2) {
        throw CropFabricException("too few parameters (2 expected)");
    } else if (input_params.size() > 2) {
        throw CropFabricException("too many parameters (2 expected)");
    }
    try {
        if (input_params[0].contains('.') || input_params[1].contains('.')) {
            throw CropFabricException("wrong filter parameter");
        }
        size_t width = static_cast<size_t>(std::stoll(input_params[0]));
        size_t height = static_cast<size_t>(std::stoll(input_params[1]));
        if (width == 0 || height == 0) {
            throw CropFabricException("wrong filter parameter");
        }
        return std::make_shared<Crop>(height, width);
    } catch (CropFabricException& e) {
        throw e;
    } catch (...) {
        throw CropFabricException("wrong filter parameter");
    }
}
