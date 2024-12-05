# advent-of-code
My personal repository for [Advent of Code](https://adventofcode.com/) using C++17

# structure
- ```include``` folder with file for helperfunctions used throughout the day
- ```y-20xx``` folder for advent of code of year 20xx
- ```y-20xx/puzzle_inputs``` folder for inputs for each day in form ```input_xx.txt```

# run
Code can be run via ```make day_xx``` in the corresponding year folder. For debug messages run ```make day_xx_debug```

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
  int lineNumb = 0;
  for (auto &&line : lines) {
    
    ++lineNumb;
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
