#include "../include/reader.h"
#include <algorithm>
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_02.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, ' ');

  int result = 0;

  int lineNumb = 0;
  for (auto &&line : lines) {
    int last = std::stoi(line[0]);
    bool increasing = std::stoi(line[0]) < std::stoi(line[1]);
    for (int number = 1; number < line.size(); ++number) {
      if ((increasing && std::stoi(line[number]) - last > 0 &&
           std::stoi(line[number]) - last < 4) ||
          (!increasing && std::stoi(line[number]) - last < 0 &&
           std::stoi(line[number]) - last > -4)) {
        last = std::stoi(line[number]);
      } else {
        if (debug && std::abs(std::stoi(line[number]) - last) > 3)
          std::cout << lineNumb << ": Distance too big: " << last << ","
                    << line[number] << "\n";
        else if (debug)
          std::cout << lineNumb << ": Directionchange/same number: " << last
                    << "," << line[number] << "\n";

        last = -1;
        break;
      }
    }
    if (last != -1) {
      ++result;
    }
    ++lineNumb;
  }

  file.close();

  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_02.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, ' ');

  int result = 0;
  int lineNumb = 0;
  for (auto &&line : lines) {
    bool possible;
    for (int skipNumber = 0; skipNumber < line.size(); skipNumber++) {
      possible = true;
      int first = (skipNumber == 0) ? 1 : 0;
      int second = (skipNumber == 1 || skipNumber == 0) ? 2 : 1;
      int last = std::stoi(line[first]);
      bool increasing = std::stoi(line[first]) < std::stoi(line[second]);
      for (int number = second; number < line.size(); ++number) {
        if (skipNumber == number)
          continue;
        if ((increasing && std::stoi(line[number]) - last > 0 &&
             std::stoi(line[number]) - last < 4) ||
            (!increasing && std::stoi(line[number]) - last < 0 &&
             std::stoi(line[number]) - last > -4)) {
          last = std::stoi(line[number]);
        } else {
          if (debug && std::abs(std::stoi(line[number]) - last) > 3)
            std::cout << lineNumb << ": Distance too big: " << last << ","
                      << line[number] << "\n";
          else if (debug)
            std::cout << lineNumb << ": Directionchange/same number: " << last
                      << "," << line[number] << "\n";
          possible = false;
          break;
        }
      }
      if (possible)
        break;
    }

    if (possible) {
      ++result;
    }
    ++lineNumb;
  }

  file.close();

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug) << "\n"; // solution: 559
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution: 601
  return 0;
}