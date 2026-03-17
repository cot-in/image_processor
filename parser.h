#pragma once
#include <string>
#include <string_view>
#include <vector>

struct FilterInput {
    std::string name;
    std::vector<std::string> filter_params;
};

struct ParserResults {
    std::string input_path;
    std::string output_path;
    std::vector<FilterInput> filters;
};

ParserResults Parse(int argc, char** argv);

bool operator==(const FilterInput& foo, const FilterInput& bar);

bool operator==(const ParserResults& foo, const ParserResults& bar);
