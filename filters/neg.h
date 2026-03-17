#pragma once
#include "base_filter.h"

class Negative : public BaseFilter {
public:
    Negative();
    void Apply(Image &image) override;
};
