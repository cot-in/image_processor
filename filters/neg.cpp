#include "neg.h"

Negative::Negative() {
}

void Negative::Apply(Image &image) {
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            RGB pixel = image.GetPixel(x, y);
            pixel.r = 1 - pixel.r;
            pixel.g = 1 - pixel.g;
            pixel.b = 1 - pixel.b;
            image.SetPixel(x, y, pixel);
        }
    }
}
