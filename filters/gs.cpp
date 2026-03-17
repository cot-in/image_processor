#include "gs.h"

constexpr double RedCoefficient = 0.299;
constexpr double GreenCoefficient = 0.587;
constexpr double BlueCoefficient = 0.114;

GrayScale::GrayScale() {
}

void GrayScale::Apply(Image &image) {
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            RGB pixel = image.GetPixel(x, y);
            pixel.r = pixel.g = pixel.b =
                RedCoefficient * pixel.r + GreenCoefficient * pixel.g + BlueCoefficient * pixel.b;
            image.SetPixel(x, y, pixel);
        }
    }
}
