#pragma once
#include "../image.h"

class BaseFilter {
public:
    virtual void Apply(Image &image) = 0;

    virtual ~BaseFilter() {
    }
};

class BaseFilterWithMatrix : public BaseFilter {
public:
    BaseFilterWithMatrix();
    explicit BaseFilterWithMatrix(const std::vector<std::vector<double>> &matrix);
    void Apply(Image &image) override;
    RGB ApplyMatrixToPixel(Image &image, size_t x, size_t y);

protected:
    std::vector<std::vector<double>> matrix_;
};
