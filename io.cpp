#include "exceptions.h"
#include "io.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <filesystem>
#include <limits>

constexpr size_t ByteSize = 8;
constexpr size_t FileHeaderSize = 14;
constexpr size_t ImageHeaderSize = 40;
constexpr size_t ColorDimension = 255;
constexpr size_t BMPType = 24;
constexpr uint16_t BMPCode = 19778;

BinaryReader::BinaryReader(const std::string& in_path) : in_(in_path) {
}

template <std::integral T>
void BinaryReader::Read(T& value) {
    value = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        uint8_t byte = 0;
        in_.read(reinterpret_cast<char*>(&byte), 1);
        value |= static_cast<T>(byte) << (i * ByteSize);
    }
}

BinaryWriter::BinaryWriter(const std::string& out_path) : out_(out_path) {
}

template <std::integral T>
void BinaryWriter::Write(T value) {
    for (size_t i = 0; i < sizeof(T); ++i) {
        uint8_t byte = static_cast<uint8_t>(value >> (i * ByteSize) & std::numeric_limits<uint8_t>::max());
        out_.write(reinterpret_cast<char*>(&byte), 1);
    }
}

Image ReadImage(const std::string& filename) {
    if (!std::filesystem::exists(filename) && !std::filesystem::is_regular_file(filename)) {
        throw ReadImageException("the image does not exist or your path is wrong");
    }
    BinaryReader reader(filename);
    uint16_t bf_type = 0;
    reader.Read(bf_type);
    if (bf_type != BMPCode) {
        throw ReadImageException("the image type is incorrect - you should use BMP");
    }
    uint32_t bf_size = 0;
    reader.Read(bf_size);
    uint16_t bf_reserved_1 = 0;
    reader.Read(bf_reserved_1);
    uint16_t bf_reserved_2 = 0;
    reader.Read(bf_reserved_2);
    if (bf_reserved_1 != 0 || bf_reserved_2 != 0) {
        throw ReadImageException("the file encoding format is broken");
    }
    uint32_t bf_off_bits = 0;
    reader.Read(bf_off_bits);
    if (bf_off_bits != FileHeaderSize + ImageHeaderSize) {
        throw ReadImageException("the file encoding format is broken");
    }
    uint32_t bi_size = 0;
    reader.Read(bi_size);
    if (bi_size != ImageHeaderSize) {
        throw ReadImageException("the file encoding format is broken");
    }
    uint32_t bi_width = 0;
    reader.Read(bi_width);
    int32_t bi_height = 0;
    reader.Read(bi_height);
    if (bi_width == 0 || bi_height == 0) {
        throw ReadImageException("only positive image sizes are allowed");
    }
    uint16_t bi_planes = 0;
    reader.Read(bi_planes);
    if (bi_planes != 1) {
        throw ReadImageException("the file encoding format is broken");
    }
    uint16_t bi_bit_count = 0;
    reader.Read(bi_bit_count);
    if (bi_bit_count != BMPType) {
        throw ReadImageException("you should use a 24-bit BMP");
    }
    uint32_t bi_compression = 0;
    reader.Read(bi_compression);
    if (bi_compression != 0) {
        throw ReadImageException("you should use BMP without compression");
    }
    uint32_t bi_size_image = 0;
    reader.Read(bi_size_image);
    uint32_t bi_x_pels_per_meter = 0;
    reader.Read(bi_x_pels_per_meter);
    uint32_t bi_y_pels_per_meter = 0;
    reader.Read(bi_y_pels_per_meter);
    uint32_t bi_crl_used = 0;
    reader.Read(bi_crl_used);
    uint32_t bi_crl_important = 0;
    reader.Read(bi_crl_important);
    if (bi_compression != 0 || bi_crl_important != 0) {
        throw ReadImageException("you should use BMP without Color Map");
    }
    bool is_upside_down = (bi_height < 0);
    bi_height = std::abs(bi_height);
    std::vector<std::vector<RGB>> image_matrix(bi_height, std::vector<RGB>(bi_width));
    uint32_t null_padded = (4 - (bi_width * 3) % 4) % 4;
    for (size_t x = 0; x < static_cast<size_t>(bi_height); ++x) {
        for (size_t y = 0; y < static_cast<size_t>(bi_width); ++y) {
            uint8_t b = 0;
            uint8_t g = 0;
            uint8_t r = 0;
            reader.Read(b);
            reader.Read(g);
            reader.Read(r);
            RGB pixel;
            pixel.b = static_cast<double>(b) / ColorDimension;
            pixel.g = static_cast<double>(g) / ColorDimension;
            pixel.r = static_cast<double>(r) / ColorDimension;
            image_matrix[x][y] = pixel;
        }
        for (uint32_t i = 0; i < null_padded; ++i) {
            uint8_t useless_byte = 0;
            reader.Read(useless_byte);
        }
    }
    if (is_upside_down) {
        std::ranges::reverse(image_matrix);
    }
    return Image(image_matrix);
}

void WriteImage(const Image& image, const std::string& filename) {
    if (!filename.ends_with(".bmp")) {
        throw WriteImageException("output file must be in BMP format");
    }
    BinaryWriter writer(filename);
    uint16_t bf_type = BMPCode;
    writer.Write(bf_type);
    uint32_t bf_size = FileHeaderSize + ImageHeaderSize + ((image.GetWidth() * 3 + 4 - 1) / 4) * 4 * image.GetHeight();
    writer.Write(bf_size);
    uint16_t bf_reserved_1 = 0;
    writer.Write(bf_reserved_1);
    uint16_t bf_reserved_2 = 0;
    writer.Write(bf_reserved_2);
    uint32_t bf_off_bits = FileHeaderSize + ImageHeaderSize;
    writer.Write(bf_off_bits);
    uint32_t bi_size = ImageHeaderSize;
    writer.Write(bi_size);
    uint32_t bi_width = image.GetWidth();
    writer.Write(bi_width);
    uint32_t bi_height = image.GetHeight();
    writer.Write(bi_height);
    uint16_t bi_planes = 1;
    writer.Write(bi_planes);
    uint16_t bi_bit_count = BMPType;
    writer.Write(bi_bit_count);
    uint32_t bi_compression = 0;
    writer.Write(bi_compression);
    uint32_t bi_size_image = 0;
    writer.Write(bi_size_image);
    uint32_t bi_x_pels_per_meter = 0;
    writer.Write(bi_x_pels_per_meter);
    uint32_t bi_y_pels_per_meter = 0;
    writer.Write(bi_y_pels_per_meter);
    uint32_t bi_clr_used = 0;
    writer.Write(bi_clr_used);
    uint32_t bi_clr_important = 0;
    writer.Write(bi_clr_important);
    uint32_t null_padded = (4 - (3 * bi_width) % 4) % 4;
    for (size_t x = 0; x < static_cast<size_t>(bi_height); ++x) {
        for (size_t y = 0; y < static_cast<size_t>(bi_width); ++y) {
            RGB pixel = image.GetPixel(x, y);
            uint8_t b = static_cast<uint8_t>(pixel.b * ColorDimension);
            uint8_t g = static_cast<uint8_t>(pixel.g * ColorDimension);
            uint8_t r = static_cast<uint8_t>(pixel.r * ColorDimension);
            writer.Write(b);
            writer.Write(g);
            writer.Write(r);
        }
        for (uint32_t i = 0; i < null_padded; ++i) {
            uint8_t useless_byte = 0;
            writer.Write(useless_byte);
        }
    }
}
