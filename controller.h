#pragma once
#include "fabrics/base_fabric.h"
#include "fabrics/blur_fabric.h"
#include "fabrics/crop_fabric.h"
#include "fabrics/crystallize_fabric.h"
#include "fabrics/edge_fabric.h"
#include "fabrics/gs_fabric.h"
#include "fabrics/neg_fabric.h"
#include "fabrics/sharpening_fabric.h"
#include "filters/base_filter.h"
#include "parser.h"
#include <unordered_map>

const std::unordered_map<std::string, std::shared_ptr<BaseFabric>> FABRICS = {
    {"crop", std::make_shared<CropFabric>()},
    {"gs", std::make_shared<GrayScaleFabric>()},
    {"neg", std::make_shared<NegativeFabric>()},
    {"sharp", std::make_shared<SharpeningFabric>()},
    {"edge", std::make_shared<EdgeDetectionFabric>()},
    {"blur", std::make_shared<BlurFabric>()},
    {"crystal", std::make_shared<CrystallizeFabric>()}};

std::vector<std::shared_ptr<BaseFilter>> CreateFilters(const ParserResults &parser_results);

void ApplyFilters(const std::vector<std::shared_ptr<BaseFilter>> &filters, Image &image);
