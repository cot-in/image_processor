#pragma once
#include "base_filter.h"

const std::vector<std::vector<double>> SHARPENING_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

class Sharpening : public BaseFilterWithMatrix {
public:
    Sharpening();
};
