# advent-of-code
Just my personal repository for [Advent of Code](https://adventofcode.com/)

# skript template
```
#include "../include/reader.h"
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_xx.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines = readFullFile(file, ' ');

  int result = 0;

  for (auto &&line : lines) {
    
  }

  file.close();

  return result;
}

int puzzleTwo(bool debug) {
  
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n"; // solution:
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug)
            << "\n"; // solution:
  return 0;
}
```
