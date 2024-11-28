#define CATCH_CONFIG_MAIN

#include "reader.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("reading one line at a time", "[line]") {
  std::fstream file("test.csv");
  std::vector<std::string> line;

  SECTION("without delimiter") {
    line = readLine(&file);
    REQUIRE(line.size() == 1);
    REQUIRE(line[0] == "Eins,Zwei,Drei");
    file.close();
  }
  SECTION("with delimiter") {
    line = readLine(&file, ',');
    REQUIRE(line.size() == 3);
    REQUIRE(line[0] == "Eins");
    REQUIRE(line[2] == "Drei");
    
    line = readLine(&file, ',');
    REQUIRE(line.size() == 3);
    REQUIRE(line[0] == "hallo");
    REQUIRE(line[2] == "alle");
    
    file.close();
  }
}