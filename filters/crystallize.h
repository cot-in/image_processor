#pragma once
#include "base_filter.h"

class Crystallize : public BaseFilter {
public:
    explicit Crystallize(uint64_t crystals);
    void Apply(Image &image) override;

private:
    uint64_t crystals_count_;
};
