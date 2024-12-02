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
  int lineNumb = 1;

  for (auto &&line : lines) {
    int last = std::stoi(line[0]);
    bool increasing = std::stoi(line[0]) < std::stoi(line[1]);

    int lastOtherPath = -1;
    int numbToSkip = line.size();
    int pathsCheckedWrong = 0;

    for (int number = 1; number < line.size(); ++number) {
      // Distance check and right direction
      if ((increasing && std::stoi(line[number]) - last > 0 &&
           std::stoi(line[number]) - last < 4) ||
          (!increasing && std::stoi(line[number]) - last < 0 &&
           std::stoi(line[number]) - last > -4)) {
        last = std::stoi(line[number]);
      } else {
        numbToSkip = number;
        lastOtherPath = (number - 2 > -1) ? std::stoi(line[number - 2]) : -1;
        break;
      }
    }

    // Path 1: sikp the number that was wrong
    for (int number = numbToSkip + 1; number < line.size(); number++) {
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

        ++pathsCheckedWrong;
        break;
      }
    }

    // Path 2: sikp the last number before the wrong
    if (lastOtherPath == -1 && numbToSkip != line.size()) {
      lastOtherPath = std::stoi(line[numbToSkip]);
      if (numbToSkip + 1 < line.size())
        increasing =
            std::stoi(line[numbToSkip]) < std::stoi(line[numbToSkip + 1]);
    }
    for (int number = numbToSkip + 1; number < line.size(); number++) {
      if ((increasing && std::stoi(line[number]) - lastOtherPath > 0 &&
           std::stoi(line[number]) - lastOtherPath < 4) ||
          (!increasing && std::stoi(line[number]) - lastOtherPath < 0 &&
           std::stoi(line[number]) - lastOtherPath > -4)) {
        lastOtherPath = std::stoi(line[number]);
      } else {
        if (debug && std::abs(std::stoi(line[number]) - lastOtherPath) > 3)
          std::cout << lineNumb << ": Distance too big: " << lastOtherPath
                    << "," << line[number] << "\n";
        else if (debug)
          std::cout << lineNumb
                    << ": Directionchange/same number: " << lastOtherPath << ","
                    << line[number] << "\n";

        ++pathsCheckedWrong;
        break;
      }
    }

    if (pathsCheckedWrong < 2) {
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
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution:
  return 0;
}