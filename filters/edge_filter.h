#pragma once
#include "base_filter.h"

const std::vector<std::vector<double>> EDGE_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

class EdgeDetection : public BaseFilterWithMatrix {
public:
    explicit EdgeDetection(double threshold);
    void Apply(Image &image) override;

private:
    double threshold_;
};
