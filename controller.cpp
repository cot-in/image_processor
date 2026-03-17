#include "controller.h"
#include "exceptions.h"

std::vector<std::shared_ptr<BaseFilter>> CreateFilters(const ParserResults &parser_results) {
    std::vector<std::shared_ptr<BaseFilter>> filters;
    for (const auto &filter : parser_results.filters) {
        auto fabric = FABRICS.find(filter.name);
        if (fabric == FABRICS.end()) {
            throw ControllerException(filter.name);
        }
        filters.push_back(fabric->second->Create(filter.filter_params));
    }
    return filters;
}

void ApplyFilters(const std::vector<std::shared_ptr<BaseFilter>> &filters, Image &image) {
    for (const auto &filter : filters) {
        filter->Apply(image);
    }
}
