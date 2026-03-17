#include "crop.h"

Crop::Crop(size_t height, size_t width) : height_(height), width_(width) {
}

void Crop::Apply(Image &image) {
    image.SetHeight(std::min(image.GetHeight(), height_));
    image.SetWidth(std::min(image.GetWidth(), width_));
}
