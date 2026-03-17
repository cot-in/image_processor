cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 23)
add_catch(parser_test tests/parser_test.cpp parser.cpp exceptions.cpp)
add_catch(image_test tests/image_test.cpp image.cpp exceptions.cpp)
add_catch(fabric_test tests/fabric_test.cpp
        fabrics/base_fabric.cpp
        fabrics/crop_fabric.cpp
        fabrics/crystallize_fabric.cpp
        fabrics/edge_fabric.cpp
        fabrics/gs_fabric.cpp
        fabrics/neg_fabric.cpp
        fabrics/sharpening_fabric.cpp
        fabrics/blur_fabric.cpp
        filters/base_filter.cpp
        filters/crop.cpp
        filters/crystallize.cpp
        filters/edge_filter.cpp
        filters/gs.cpp
        filters/neg.cpp
        filters/sharpening.cpp
        filters/blur.cpp
        image.cpp
        exceptions.cpp)
add_executable(
        image_processor
        image_processor.cpp
        fabrics/base_fabric.cpp
        fabrics/crop_fabric.cpp
        fabrics/crystallize_fabric.cpp
        fabrics/edge_fabric.cpp
        fabrics/gs_fabric.cpp
        fabrics/neg_fabric.cpp
        fabrics/sharpening_fabric.cpp
        fabrics/blur_fabric.cpp
        filters/base_filter.cpp
        filters/crop.cpp
        filters/crystallize.cpp
        filters/edge_filter.cpp
        filters/gs.cpp
        filters/neg.cpp
        filters/sharpening.cpp
        filters/blur.cpp
        controller.cpp
        image.cpp
        io.cpp
        parser.cpp
        exceptions.cpp
)
