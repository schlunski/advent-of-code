#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <tuple>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_03.txt");
  std::vector<std::string> line = read_line<std::string>(file);

  int result = 1;

  int posX = 0;
  int posY = 0;
  std::vector<std::tuple<int, int>> checkedHouses = {
      std::tuple<int, int>{0, 0}};
  if (debug)
    std::cout << "{" << 0 << "," << 0 << "}, ";

  for (auto &&direction : line[0]) {
    switch (direction) {
    case '^':
      ++posY;
      break;
    case 'v':
      --posY;
      break;
    case '>':
      ++posX;
      break;
    case '<':
      --posX;
      break;
    }

    if (std::find(
            checkedHouses.begin(), checkedHouses.end(),
            std::tuple<int, int>{posY, posX}) == checkedHouses.end()) {
      ++result;
      checkedHouses.push_back({posY, posX});
      if (debug)
        std::cout << "{" << posY << "," << posX << "}, ";
    }
  }

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_03.txt");
  std::vector<std::string> line = read_line<std::string>(file);

  int result = 1;
  bool roboSanta = false;

  int posXRoboSanta = 0;
  int posYRoboSanta = 0;
  int posX = 0;
  int posY = 0;
  std::vector<std::tuple<int, int>> checkedHouses = {
      std::tuple<int, int>{0, 0}};
  if (debug)
    std::cout << "{" << 0 << "," << 0 << "}, ";

  for (auto &&direction : line[0]) {
    switch (direction) {
    case '^':
      if (roboSanta) {
        ++posYRoboSanta;
      } else {
        ++posY;
      }
      break;
    case 'v':
      if (roboSanta) {
        --posYRoboSanta;
      } else {
        --posY;
      }
      break;
    case '>':
      if (roboSanta) {
        ++posXRoboSanta;
      } else {
        ++posX;
      }
      break;
    case '<':
      if (roboSanta) {
        --posXRoboSanta;
      } else {
        --posX;
      }
      break;
    }

    if (!roboSanta &&
        std::find(
            checkedHouses.begin(), checkedHouses.end(),
            std::tuple<int, int>{posY, posX}) == checkedHouses.end()) {
      ++result;
      checkedHouses.push_back({posY, posX});
      if (debug)
        std::cout << "S: {" << posY << "," << posX << "}, ";
    } else if (
        roboSanta && std::find(
                         checkedHouses.begin(), checkedHouses.end(),
                         std::tuple<int, int>{posYRoboSanta, posXRoboSanta}) ==
                         checkedHouses.end()) {
      ++result;
      checkedHouses.push_back({posYRoboSanta, posXRoboSanta});
      if (debug)
        std::cout << "RS: {" << posYRoboSanta << "," << posXRoboSanta << "}, ";
    }

    roboSanta = !roboSanta;
  }

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n"; // solution: 2565
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug)
            << "\n"; // solution: 2639
  return 0;
}