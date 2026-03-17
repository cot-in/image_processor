#include <catch.hpp>
#include "../parser.h"
#include "../exceptions.h"

TEST_CASE("Bad input") {
    SECTION("Only input file") {
        const char* args[] = {"binary", "input_path"};
        REQUIRE_THROWS_WITH(Parse(2, const_cast<char**>(args)), "Could not parse input because of no output file name");
    }

    SECTION("After files goes non-filter (string)") {
        const char* args[] = {"binary", "input_path", "output_path", "something"};
        REQUIRE_THROWS_WITH(Parse(4, const_cast<char**>(args)),
                            "Could not parse input because of the filter parameters should go after filter's name");
    }

    SECTION("After files goes non-filter (integer)") {
        const char* args[] = {"binary", "input_path", "output_path", "52"};
        REQUIRE_THROWS_WITH(Parse(4, const_cast<char**>(args)),
                            "Could not parse input because of the filter parameters should go after filter's name");
    }
}

TEST_CASE("Good input") {
    SECTION("One filter without parameters") {
        const char* args[] = {"binary", "input_path", "output_path", "-gs"};
        FilterInput filter1{"gs", {}};
        ParserResults expected{"input_path", "output_path", {filter1}};
        REQUIRE(Parse(4, const_cast<char**>(args)) == expected);
    }

    SECTION("One filter with parameters") {
        const char* args[] = {"binary", "input_path", "output_path", "-crop", "200", "100"};
        FilterInput filter1{"crop", {"200", "100"}};
        ParserResults expected{"input_path", "output_path", {filter1}};
        REQUIRE(Parse(6, const_cast<char**>(args)) == expected);
    }

    SECTION("Two filters") {
        const char* args[] = {"binary", "input_path", "output_path", "-crop", "200", "100", "-blur", "1.25"};
        FilterInput filter1{"crop", {"200", "100"}};
        FilterInput filter2{"blur", {"1.25"}};
        ParserResults expected{"input_path", "output_path", {filter1, filter2}};
        REQUIRE(Parse(8, const_cast<char**>(args)) == expected);
    }

    SECTION("Many filters") {
        const char* args[] = {"binary", "input_path", "output_path", "-crop", "200",      "100",
                              "-blur",  "1.25",       "-gs",         "-neg",  "-crystal", "1200"};
        FilterInput filter1{"crop", {"200", "100"}};
        FilterInput filter2{"blur", {"1.25"}};
        FilterInput filter3{"gs"};
        FilterInput filter4{"neg"};
        FilterInput filter5{"crystal", {"1200"}};
        ParserResults expected{"input_path", "output_path", {filter1, filter2, filter3, filter4, filter5}};
        REQUIRE(Parse(12, const_cast<char**>(args)) == expected);
    }

    SECTION("After files no filters") {
        const char* args[] = {"binary", "input_path", "output_path"};
        ParserResults expected{"input_path", "output_path", {}};
        REQUIRE(Parse(3, const_cast<char**>(args)) == expected);
    }
}
