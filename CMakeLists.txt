cmake_minimum_required(VERSION 3.20)
project(image_processor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

option(IMAGE_PROCESSOR_BUILD_TESTS "Build unit tests" ON)
option(IMAGE_PROCESSOR_SANITIZE "Build with AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>
)
if (IMAGE_PROCESSOR_SANITIZE)
    target_compile_options(project_options INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(project_options INTERFACE -fsanitize=address,undefined)
endif ()

add_library(image_processor_lib STATIC
        image.cpp
        io.cpp
        parser.cpp
        controller.cpp
        exceptions.cpp
        filters/base_filter.cpp
        filters/blur.cpp
        filters/crop.cpp
        filters/crystallize.cpp
        filters/edge_filter.cpp
        filters/gs.cpp
        filters/neg.cpp
        filters/sharpening.cpp
        fabrics/base_fabric.cpp
        fabrics/blur_fabric.cpp
        fabrics/crop_fabric.cpp
        fabrics/crystallize_fabric.cpp
        fabrics/edge_fabric.cpp
        fabrics/gs_fabric.cpp
        fabrics/neg_fabric.cpp
        fabrics/sharpening_fabric.cpp
)
target_include_directories(image_processor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(image_processor_lib PUBLIC project_options)

add_executable(image_processor image_processor.cpp)
target_link_libraries(image_processor PRIVATE image_processor_lib)

if (IMAGE_PROCESSOR_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.7.1
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    include(Catch)

    foreach (test_name parser_test image_test fabric_test)
        add_executable(${test_name} tests/${test_name}.cpp)
        target_link_libraries(${test_name} PRIVATE image_processor_lib Catch2::Catch2WithMain)
        catch_discover_tests(${test_name})
    endforeach ()
endif ()
