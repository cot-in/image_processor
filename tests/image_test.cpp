#include <catch.hpp>
#include "../image.h"
#include "../exceptions.h"

TEST_CASE("Set and get pixels") {
    std::vector<std::vector<RGB>> empty_image;
    Image image{empty_image};
    REQUIRE(image.GetHeight() == 0);
    REQUIRE(image.GetWidth() == 0);
    const double double_number = 0.1;
    std::vector<std::vector<RGB>> new_image = {{{double_number, 1, 1}, {2, 2, 1}, {3, 3, 3}},
                                               {{4, 4, 4}, {0, 0, 0}, {1, 2, 3}}};
    image.SetPixels(new_image);
    REQUIRE(image.GetHeight() == new_image.size());
    REQUIRE(image.GetWidth() == new_image[0].size());
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            REQUIRE(image.GetPixel(x, y) == new_image[x][y]);
            new_image[x][y].r += 2;
            new_image[x][y].g += 3;
            new_image[x][y].b -= 1;
            image.SetPixel(x, y, new_image[x][y]);
            REQUIRE(image.GetPixel(x, y) == new_image[x][y]);
        }
    }
    RGB new_pixel{0, double_number, 1};
    image.SetPixel(0, 0, new_pixel);
    REQUIRE(image.GetPixel(0, 0) == new_pixel);
    image.SetWidth(0);
    image.SetHeight(0);
    REQUIRE(image.GetHeight() == 0);
    REQUIRE(image.GetWidth() == 0);
}
