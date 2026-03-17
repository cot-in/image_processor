#pragma once
#include "base_filter.h"

class GrayScale : public BaseFilter {
public:
    GrayScale();
    void Apply(Image &image) override;
};
