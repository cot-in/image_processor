#pragma once
#include "image.h"
#include <fstream>
#include <string>

class BinaryReader {
public:
    explicit BinaryReader(const std::string& in_path);

    template <std::integral T>
    void Read(T& value);

private:
    std::ifstream in_;
};

class BinaryWriter {
public:
    explicit BinaryWriter(const std::string& out_path);

    template <std::integral T>
    void Write(T value);

private:
    std::ofstream out_;
};

Image ReadImage(const std::string& filename);

void WriteImage(const Image& image, const std::string& filename);
