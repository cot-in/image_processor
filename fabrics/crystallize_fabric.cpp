#include "crystallize_fabric.h"
#include "../exceptions.h"
#include "../filters/crystallize.h"

std::shared_ptr<BaseFilter> CrystallizeFabric::Create(const std::vector<std::string> &input_params) {
    if (input_params.empty()) {
        throw CrystallizeFabricException("too few parameters (1 expected)");
    } else if (input_params.size() > 1) {
        throw CrystallizeFabricException("too many parameters (1 expected)");
    }
    try {
        if (input_params[0].contains('.')) {
            throw CrystallizeFabricException("wrong filter parameter");
        }
        uint64_t crystals = std::stoll(input_params[0]);
        if (crystals == 0) {
            throw CrystallizeFabricException("wrong filter parameter");
        }
        return std::make_shared<Crystallize>(crystals);
    } catch (CrystallizeFabricException &e) {
        throw e;
    } catch (...) {
        throw CrystallizeFabricException("wrong filter parameter");
    }
}
