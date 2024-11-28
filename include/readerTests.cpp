#define CATCH_CONFIG_MAIN

#include "reader.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("reading one line at a time", "[readLine]") {
  std::fstream file("test.csv");
  std::vector<std::string> line;

  SECTION("without delimiter") {
    line = readLine(file);
    REQUIRE(line.size() == 1);
    REQUIRE(line[0] == "Eins,Zwei,Drei");
    file.close();
  }
  SECTION("with delimiter") {
    line = readLine(file, ',');
    REQUIRE(line.size() == 3);
    REQUIRE(line[0] == "Eins");
    REQUIRE(line[2] == "Drei");

    line = readLine(file, ',');
    REQUIRE(line.size() == 3);
    REQUIRE(line[0] == "hallo");
    REQUIRE(line[2] == "alle");
    file.close();
  }
}

TEST_CASE("reading full file", "[readFullFile]") {
  std::fstream file("test.csv");
  std::vector<std::vector<std::string>> lines;
  
  SECTION("columnwise") {
    SECTION("without skipping lines") {
      lines = readFullFile(file, ',');
      REQUIRE(lines.size() == 3);
      REQUIRE(lines[0].size() == 3);
      REQUIRE(lines[1][0] == "Zwei");
      file.close();
    }
    SECTION("with skipping lines") {
      lines = readFullFile(file, ',', 1);
      REQUIRE(lines.size() == 3);
      REQUIRE(lines[0].size() == 2);
      REQUIRE(lines[0][0] == "hallo");
      REQUIRE(lines[1][0] == "ihr");
      REQUIRE(lines[2][0] == "alle");
      REQUIRE(lines[1][1] == "hier");
      file.close();
    }
  }

  SECTION("rowwise") {
    SECTION("without skipping lines") {
      lines = readFullFile(file, ',', 0, false);
      REQUIRE(lines.size() == 3);
      REQUIRE(lines[0][0] == "Eins");
      REQUIRE(lines[0][1] == "Zwei");
      file.close();
    }
    SECTION("with skipping lines") {
      lines = readFullFile(file, ',', 2, false);
      REQUIRE(lines.size() == 1);
      REQUIRE(lines[0][0] == "was");
      REQUIRE(lines[0][1] == "hier");
      REQUIRE(lines[0][2] == "los");
      file.close();
    }
  }
}

TEST_CASE("Trimming strings", "[trim]") {
  std::string word("   basic   ");
  REQUIRE(trim(word, ' ') == "basic");
  REQUIRE(word == "basic");
  
  word = ";testing;;";
  REQUIRE(trim(word, ';') == "testing");
  REQUIRE(word == "testing");
}