#pragma once
#include <stdexcept>
#include <string>

class ImageProcessorException : public std::exception {
public:
    const char* what() const noexcept final;

protected:
    std::string message_;
};

class ParserException : public ImageProcessorException {
public:
    explicit ParserException(const std::string& message);
};

class ReadImageException : public ImageProcessorException {
public:
    explicit ReadImageException(const std::string& message);
};

class WriteImageException : public ImageProcessorException {
public:
    explicit WriteImageException(const std::string& message);
};

class ControllerException : public ImageProcessorException {
public:
    explicit ControllerException(const std::string& message);
};

class BlurFabricException : public ImageProcessorException {
public:
    explicit BlurFabricException(const std::string& message);
};

class CropFabricException : public ImageProcessorException {
public:
    explicit CropFabricException(const std::string& message);
};

class GrayScaleFabricException : public ImageProcessorException {
public:
    explicit GrayScaleFabricException(const std::string& message);
};

class NegativeFabricException : public ImageProcessorException {
public:
    explicit NegativeFabricException(const std::string& message);
};

class SharpeningFabricException : public ImageProcessorException {
public:
    explicit SharpeningFabricException(const std::string& message);
};

class EdgeDetectionFabricException : public ImageProcessorException {
public:
    explicit EdgeDetectionFabricException(const std::string& message);
};

class CrystallizeFabricException : public ImageProcessorException {
public:
    explicit CrystallizeFabricException(const std::string& message);
};
