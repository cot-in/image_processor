#include "edge_filter.h"
#include "../fabrics/gs_fabric.h"

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
    matrix_ = EDGE_MATRIX;
}

void EdgeDetection::Apply(Image &image) {
    GrayScaleFabric gray;
    gray.Create({})->Apply(image);
    BaseFilterWithMatrix::Apply(image);
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            RGB pixel;
            if (image.GetPixel(x, y).r > threshold_) {
                pixel.r = pixel.g = pixel.b = 1;
            } else {
                pixel.r = pixel.g = pixel.b = 0;
            }
            image.SetPixel(x, y, pixel);
        }
    }
}
