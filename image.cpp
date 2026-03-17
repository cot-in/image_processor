#include "image.h"
#include <algorithm>
#include <ranges>

Image::Image(std::vector<std::vector<RGB>> &image) : image_(image) {
}

size_t Image::GetHeight() const {
    return image_.size();
}

size_t Image::GetWidth() const {
    if (GetHeight() == 0) {
        return 0;
    }
    return image_[0].size();
}

void Image::SetHeight(size_t height) {
    std::ranges::reverse(image_);
    image_.resize(height);
    std::ranges::reverse(image_);
}

void Image::SetWidth(size_t width) {
    for (size_t x = 0; x < GetHeight(); ++x) {
        image_[x].resize(width);
    }
}

RGB Image::GetPixel(size_t x, size_t y) const {
    return image_[x][y];
}

void Image::SetPixel(size_t x, size_t y, RGB pixel) {
    image_[x][y] = pixel;
}

void Image::SetPixels(const std::vector<std::vector<RGB>> &pixels) {
    image_ = pixels;
}

bool operator==(const RGB &foo, const RGB &bar) {
    return foo.r == bar.r && foo.g == bar.g && foo.b == bar.b;
}
