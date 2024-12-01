# advent-of-code
Just my personal repository for [Advent of Code](https://adventofcode.com/)

# skript template
```
#include "../include/reader.h"
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_xx.txt");
  std::vector<std::vector<std::string>> collums =
      readFullFile(file, ' ', 0, false);

  int result = 0;

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}
int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_xx.txt");
  std::vector<std::vector<std::string>> collums =
      readFullFile(file, ' ', 0, false);

  int result = 0;

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}
int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n"; // solution:
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug)
            << "\n"; // solution
  return 0;
}
```