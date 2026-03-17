#pragma once
#include "base_filter.h"

class Blur : public BaseFilter {
public:
    explicit Blur(double sigma);
    void Apply(Image &image) override;

private:
    double sigma_;
};
