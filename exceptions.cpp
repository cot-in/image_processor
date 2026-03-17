#include "exceptions.h"

const char* ImageProcessorException::what() const noexcept {
    return message_.c_str();
}

ParserException::ParserException(const std::string& message) {
    message_ = "Could not parse input because of " + message;
}

ReadImageException::ReadImageException(const std::string& message) {
    message_ = "Could not read image because of " + message;
}

WriteImageException::WriteImageException(const std::string& message) {
    message_ = "Could not write image because of " + message;
}

ControllerException::ControllerException(const std::string& filter_name) {
    message_ = "Could not find a filter named \"" + filter_name + "\"";
}

BlurFabricException::BlurFabricException(const std::string& message) {
    message_ = "Could not create Gaussian Blur filter because of " + message;
}

CropFabricException::CropFabricException(const std::string& message) {
    message_ = "Could not create Crop filter because of " + message;
}

GrayScaleFabricException::GrayScaleFabricException(const std::string& message) {
    message_ = "Could not create Grayscale filter because of " + message;
}

NegativeFabricException::NegativeFabricException(const std::string& message) {
    message_ = "Could not create Negative filter because of " + message;
}

SharpeningFabricException::SharpeningFabricException(const std::string& message) {
    message_ = "Could not create Sharpening filter because of " + message;
}

EdgeDetectionFabricException::EdgeDetectionFabricException(const std::string& message) {
    message_ = "Could not create Edge Detection filter because of " + message;
}

CrystallizeFabricException::CrystallizeFabricException(const std::string& message) {
    message_ = "Could not create Crystallize filter because of " + message;
}
