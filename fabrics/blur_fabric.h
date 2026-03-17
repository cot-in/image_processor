#pragma once
#include "base_fabric.h"

class BlurFabric : public BaseFabric {
public:
    std::shared_ptr<BaseFilter> Create(const std::vector<std::string> &input_params) override;
    ~BlurFabric() override = default;
};
