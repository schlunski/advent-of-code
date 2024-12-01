#include "../include/reader.h"
#include <algorithm>
#include <iostream>

int puzzleOne(bool debug = false) {
  std::fstream file("puzzle_inputs/input_01.txt");
  std::vector<std::vector<std::string>> collums =
      readFullFile(file, ' ', 0, true);

  int result = 0;

  // sort collums by number
  std::sort(collums[0].begin(), collums[0].end());
  std::sort(collums[3].begin(), collums[3].end());

  for (int i = 0; i < collums[0].size(); ++i) {
    int distance =
        std::abs(std::stoi(collums[0][i]) - std::stoi(collums[3][i]));

    if (debug)
      std::cout << distance << "+";

    result += distance;
  }

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int puzzleTwo(bool debug = false) {
  std::fstream file("puzzle_inputs/input_01.txt");
  std::vector<std::vector<std::string>> collums =
      readFullFile(file, ' ', 0, true);

  int result = 0;

  // sort collums by number
  std::sort(collums[0].begin(), collums[0].end());
  std::sort(collums[3].begin(), collums[3].end());

  for (auto &&leftNumber : collums[0]) {
    int count = 0;
    int left = std::stoi(leftNumber);
    for (auto &&rightNumber : collums[3]) {
      int right = std::stoi(rightNumber);
      if (left == right) {
        ++count;
      } else if (left < right) {
        break;
      }
    }
    int simScore = left * count;
    if (debug)
      std::cout << simScore << "+";

    result += simScore;
  }

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n"; // solution: 1651298
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug)
            << "\n"; // solution 21306195
  return 0;
}