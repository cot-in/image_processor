#include "base_filter.h"
#include <cstdint>

BaseFilterWithMatrix::BaseFilterWithMatrix() {
}

BaseFilterWithMatrix::BaseFilterWithMatrix(const std::vector<std::vector<double>> &matrix) {
    matrix_ = matrix;
}

size_t CheckBoundaries(int64_t coord, int64_t lft, int64_t rgh, int64_t delta) {
    if (coord + delta < lft) {
        return lft;
    } else if (coord + delta > rgh) {
        return rgh;
    } else {
        return coord + delta;
    }
}

RGB BaseFilterWithMatrix::ApplyMatrixToPixel(Image &image, size_t x, size_t y) {
    RGB new_pixel;
    new_pixel.r = 0;
    new_pixel.g = 0;
    new_pixel.b = 0;
    int64_t matrix_x = static_cast<int64_t>(matrix_.size()) / 2;
    int64_t matrix_y = static_cast<int64_t>(matrix_[0].size()) / 2;
    for (int64_t dx = -matrix_x; dx <= matrix_x; ++dx) {
        for (int64_t dy = -matrix_y; dy <= matrix_y; ++dy) {
            size_t cx = CheckBoundaries(static_cast<int64_t>(x), 0, static_cast<int64_t>(image.GetHeight()) - 1, dx);
            size_t cy = CheckBoundaries(static_cast<int64_t>(y), 0, static_cast<int64_t>(image.GetWidth()) - 1, dy);
            new_pixel.r += image.GetPixel(cx, cy).r * static_cast<double>(matrix_[dx + matrix_x][dy + matrix_y]);
            new_pixel.g += image.GetPixel(cx, cy).g * static_cast<double>(matrix_[dx + matrix_x][dy + matrix_y]);
            new_pixel.b += image.GetPixel(cx, cy).b * static_cast<double>(matrix_[dx + matrix_x][dy + matrix_y]);
        }
    }
    new_pixel.r = std::max(0.0, std::min(new_pixel.r, 1.0));
    new_pixel.g = std::max(0.0, std::min(new_pixel.g, 1.0));
    new_pixel.b = std::max(0.0, std::min(new_pixel.b, 1.0));
    return new_pixel;
}

void BaseFilterWithMatrix::Apply(Image &image) {
    std::vector<std::vector<RGB>> new_matrix(image.GetHeight(), std::vector<RGB>(image.GetWidth()));
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            new_matrix[x][y] = ApplyMatrixToPixel(image, x, y);
        }
    }
    image.SetPixels(new_matrix);
}
