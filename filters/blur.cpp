#include "blur.h"
#include <cmath>

constexpr int32_t MatrixLengthCoefficient = 6;

Blur::Blur(double sigma) : sigma_(sigma) {
}

void Blur::Apply(Image &image) {
    int32_t length = MatrixLengthCoefficient * static_cast<int32_t>(sigma_) + 1;
    std::vector<std::vector<double>> matrix(1, std::vector<double>(length));
    for (int32_t i = 0; i < length; ++i) {
        matrix[0][i] = exp(-((i - length / 2) * (i - length / 2)) / (2 * sigma_ * sigma_));
    }
    double sum = 0;
    for (int32_t i = 0; i < length; ++i) {
        sum += matrix[0][i];
    }
    for (int32_t i = 0; i < length; ++i) {
        matrix[0][i] /= sum;
    }
    std::vector<std::vector<double>> transported_matrix(length, std::vector<double>(1));
    for (int32_t i = 0; i < length; ++i) {
        transported_matrix[i][0] = matrix[0][i];
    }
    BaseFilterWithMatrix(matrix).Apply(image);
    BaseFilterWithMatrix(transported_matrix).Apply(image);
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            RGB new_pixel = image.GetPixel(x, y);
            new_pixel.r = std::max(0.0, std::min(1.0, new_pixel.r));
            new_pixel.g = std::max(0.0, std::min(1.0, new_pixel.g));
            new_pixel.b = std::max(0.0, std::min(1.0, new_pixel.b));
            image.SetPixel(x, y, new_pixel);
        }
    }
}
