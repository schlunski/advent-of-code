#include "../include/reader.h"
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_01.txt");
  std::vector<std::string> line = readLine(file);

  int result = 0;

  for (auto &&character : line[0]) {
    if (character == '(') {
      ++result;
    } else if (character == ')') {
      --result;
    }
  }

  file.close();

  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_01.txt");
  std::vector<std::string> line = readLine(file);

  int floor = 0;
  int result = 0;

  for (auto &&character : line[0]) {
    ++result;
    if (character == '(') {
      ++floor;
    } else if (character == ')') {
      --floor;
    }
    if (floor < 0) {
      break;
    }
  }

  file.close();

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug) << "\n"; // solution: 280
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution: 1797
  return 0;
}