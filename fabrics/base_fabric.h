#pragma once
#include "../filters/base_filter.h"
#include "../parser.h"
#include <memory>

class BaseFabric {
public:
    virtual std::shared_ptr<BaseFilter> Create(const std::vector<std::string> &input_params) = 0;
    virtual ~BaseFabric() = default;
};
