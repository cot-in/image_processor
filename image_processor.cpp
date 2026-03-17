#include "controller.h"
#include "exceptions.h"
#include "io.h"
#include "parser.h"
#include <iostream>

const std::string HELP =
    "usage: {program name} {input file path} {output file path} [-{filter name 1} [filter parameter 1] [filter "
    "parameter 2] ...] [-{filter name 2} [filter parameter 1] [filter parameter 2] ...] ...\n\n"
    "Supported image format:\n"
    "The input and output images must be in 24-bit BMP format without compression and without The Color Table. "
    "The type of DIB header used is BITMAPINFOHEADER.\n\n"
    "The program supports the following filters:\n"
    "1) Crop (-crop width height)\n"
    "Crops the image to the specified width and height. The upper left part of the image is used.\n"
    "The width and height must be natural numbers.\n"
    "2) Grayscale (-gs)\n"
    "3) Negative (-neg)\n"
    "4) Sharpening (-sharp)\n"
    "Increase the sharpness.\n"
    "5) Edge Detection (-edge threshold)\n"
    "Border selection. threshold must be positive number.\n"
    "6) Gaussian Blur (-blur sigma)\n"
    "sigma must be a positive number.\n"
    "7) Crystallize (-crystal crystals_count)\n"
    "Makes the image crystallized. "
    "crystals_count means how many crystals the image will be divided into.\n"
    "hint: To achieve the best result, choose crystals_count value commensurate with the number of pixels in the image.\n"
    "crystals_count must be natural number.";

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << HELP << std::endl;
        return 0;
    }
    try {
        auto parser_results = Parse(argc, argv);
        auto image = ReadImage(parser_results.input_path);
        auto filters = CreateFilters(parser_results);
        ApplyFilters(filters, image);
        WriteImage(image, parser_results.output_path);
    } catch (ImageProcessorException& exc) {
        std::cerr << exc.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
    return 0;
}
