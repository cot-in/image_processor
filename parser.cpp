#include "parser.h"
#include "exceptions.h"

ParserResults Parse(int argc, char** argv) {
    if (argc == 2) {
        throw ParserException("no output file name");
    }
    ParserResults parser_results;
    parser_results.input_path = argv[1];
    parser_results.output_path = argv[2];
    parser_results.filters = {};
    std::vector<std::vector<std::string_view>> filters;
    for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
        std::string_view current = argv[i];
        if (current[0] == '-') {
            filters.push_back(std::vector<std::string_view>());
        }
        if (filters.empty()) {
            throw ParserException("the filter parameters should go after filter's name");
        }
        filters.back().emplace_back(current);
    }
    for (auto& full_filter : filters) {
        FilterInput filter;
        filter.name = full_filter[0].substr(1);
        for (size_t i = 1; i < full_filter.size(); ++i) {
            filter.filter_params.emplace_back(full_filter[i]);
        }
        parser_results.filters.emplace_back(filter);
    }
    return parser_results;
}

bool operator==(const FilterInput& foo, const FilterInput& bar) {
    return foo.name == bar.name && foo.filter_params == bar.filter_params;
}

bool operator==(const ParserResults& foo, const ParserResults& bar) {
    return foo.input_path == bar.input_path && foo.output_path == bar.output_path && foo.filters == bar.filters;
}
