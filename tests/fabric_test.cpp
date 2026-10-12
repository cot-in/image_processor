#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include "../fabrics/blur_fabric.h"
#include "../fabrics/crop_fabric.h"
#include "../fabrics/crystallize_fabric.h"
#include "../fabrics/edge_fabric.h"
#include "../fabrics/gs_fabric.h"
#include "../fabrics/neg_fabric.h"
#include "../fabrics/sharpening_fabric.h"

TEST_CASE("Bad input") {
    SECTION("Blur Filter") {
        BlurFabric example;
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{}),
                            "Could not create Gaussian Blur filter because of too few parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"20", "25"}),
                            "Could not create Gaussian Blur filter because of too many parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"abcd", "25"}),
                            "Could not create Gaussian Blur filter because of too many parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"0"}),
                            "Could not create Gaussian Blur filter because of sigma should be positive");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"abacaba"}),
                            "Could not create Gaussian Blur filter because of wrong filter parameter");
    }

    SECTION("Crop Filter") {
        CropFabric example;
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{}),
                            "Could not create Crop filter because of too few parameters (2 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"0"}),
                            "Could not create Crop filter because of too few parameters (2 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"20", "25", "30"}),
                            "Could not create Crop filter because of too many parameters (2 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"0", "20"}),
                            "Could not create Crop filter because of wrong filter parameter");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"52", "0"}),
                            "Could not create Crop filter because of wrong filter parameter");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"52.1", "12"}),
                            "Could not create Crop filter because of wrong filter parameter");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"abacaba", "4"}),
                            "Could not create Crop filter because of wrong filter parameter");
    }

    SECTION("Crystallize Filter") {
        CrystallizeFabric example;
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{}),
                            "Could not create Crystallize filter because of too few parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"1", "2"}),
                            "Could not create Crystallize filter because of too many parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"0"}),
                            "Could not create Crystallize filter because of wrong filter parameter");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"1.2"}),
                            "Could not create Crystallize filter because of wrong filter parameter");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"abcde"}),
                            "Could not create Crystallize filter because of wrong filter parameter");
    }

    SECTION("Edge Detection Filter") {
        EdgeDetectionFabric example;
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{}),
                            "Could not create Edge Detection filter because of too few parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"1", "2"}),
                            "Could not create Edge Detection filter because of too many parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"abc", "2"}),
                            "Could not create Edge Detection filter because of too many parameters (1 expected)");
        REQUIRE_THROWS_WITH(example.Create(std::vector<std::string>{"abacaba"}),
                            "Could not create Edge Detection filter because of wrong filter parameter");
    }

    SECTION("Grayscale Filter") {
        GrayScaleFabric example;
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"4"}),
            "Could not create Grayscale filter because of the filter does not require any parameters for itself");
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"abc", "2"}),
            "Could not create Grayscale filter because of the filter does not require any parameters for itself");
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"abacaba"}),
            "Could not create Grayscale filter because of the filter does not require any parameters for itself");
    }

    SECTION("Negative Filter") {
        NegativeFabric example;
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"4"}),
            "Could not create Negative filter because of the filter does not require any parameters for itself");
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"abc", "2"}),
            "Could not create Negative filter because of the filter does not require any parameters for itself");
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"abacaba"}),
            "Could not create Negative filter because of the filter does not require any parameters for itself");
    }

    SECTION("Sharpening Filter") {
        SharpeningFabric example;
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"4"}),
            "Could not create Sharpening filter because of the filter does not require any parameters for itself");
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"abc", "2"}),
            "Could not create Sharpening filter because of the filter does not require any parameters for itself");
        REQUIRE_THROWS_WITH(
            example.Create(std::vector<std::string>{"abacaba"}),
            "Could not create Sharpening filter because of the filter does not require any parameters for itself");
    }
}

TEST_CASE("Good input") {
    SECTION("Blur Filter") {
        BlurFabric example;
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"0.05"}));
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"52"}));
    }

    SECTION("Crop Filter") {
        CropFabric example;
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"20", "40"}));
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"1", "1"}));
    }

    SECTION("Crystallize Filter") {
        CrystallizeFabric example;
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"1"}));
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"300000000"}));
    }

    SECTION("Edge Detection Filter") {
        EdgeDetectionFabric example;
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"0"}));
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"0.5"}));
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"52"}));
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{"1000.004"}));
    }

    SECTION("Grayscale Filter") {
        GrayScaleFabric example;
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{}));
    }

    SECTION("Negative Filter") {
        NegativeFabric example;
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{}));
    }

    SECTION("Sharpening Filter") {
        SharpeningFabric example;
        REQUIRE_NOTHROW(example.Create(std::vector<std::string>{}));
    }
}
