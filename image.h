#pragma once
#include <vector>

struct RGB {
    double r;
    double g;
    double b;
};

class Image {
public:
    explicit Image(std::vector<std::vector<RGB>> &image);

    size_t GetHeight() const;

    size_t GetWidth() const;

    void SetHeight(size_t height);

    void SetWidth(size_t width);

    RGB GetPixel(size_t x, size_t y) const;

    void SetPixel(size_t x, size_t y, RGB pixel);

    void SetPixels(const std::vector<std::vector<RGB>> &pixels);

private:
    std::vector<std::vector<RGB>> image_;
};

bool operator==(const RGB &foo, const RGB &bar);
