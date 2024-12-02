#include "../include/reader.h"
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_06.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, ' ');

  std::vector<std::vector<bool>> lightsGrid(false);
  lightsGrid.resize(1000);
  for (int i = 0; i < 1000; i++) {
    lightsGrid[i].resize(1000, false);
  }

  for (auto &&line : lines) {
    // delete turn from instructions
    if (line.size() > 4) {
      line.erase(line.begin());
    }
    int startX = std::stoi(seperate(line[1], ',')[0]);
    int startY = std::stoi(seperate(line[1], ',')[1]);

    int endX = std::stoi(seperate(line[3], ',')[0]);
    int endY = std::stoi(seperate(line[3], ',')[1]);

    if (line[0] == "toggle") {
      for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
          lightsGrid[y][x] = !lightsGrid[y][x];
        }
      }
      continue;
    }

    for (int x = startX; x <= endX; x++) {
      for (int y = startY; y <= endY; y++) {
        lightsGrid[y][x] = (line[0] == "on");
      }
    }
  }

  file.close();

  int result = 0;
  for (auto &&line : lightsGrid) {
    for (auto &&light : line) {
      if (light)
        ++result;
    }
  }

  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_06.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, ' ');

  std::vector<std::vector<int>> lightsGrid(false);
  lightsGrid.resize(1000);
  for (int i = 0; i < 1000; i++) {
    lightsGrid[i].resize(1000, 0);
  }

  for (auto &&line : lines) {
    // delete turn from instructions
    if (line.size() > 4) {
      line.erase(line.begin());
    }
    int startX = std::stoi(seperate(line[1], ',')[0]);
    int startY = std::stoi(seperate(line[1], ',')[1]);

    int endX = std::stoi(seperate(line[3], ',')[0]);
    int endY = std::stoi(seperate(line[3], ',')[1]);

    if (line[0] == "toggle") {
      for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
          lightsGrid[y][x] += 2;
        }
      }
      continue;
    }

    for (int x = startX; x <= endX; x++) {
      for (int y = startY; y <= endY; y++) {
        lightsGrid[y][x] += (line[0] == "on") ? 1 : -1;
        lightsGrid[y][x] = (lightsGrid[y][x] < 0) ? 0 : lightsGrid[y][x];
      }
    }
  }

  file.close();

  int result = 0;
  for (auto &&line : lightsGrid) {
    for (auto &&light : line) {
      result += light;
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug) << "\n"; // solution: 543903
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution: 14687245
  return 0;
}