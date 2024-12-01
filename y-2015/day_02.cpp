#include "../include/reader.h"
#include <algorithm>
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_02.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, 'x');

  int result = 0;

  for (auto &&line : lines) {
    // l := 0, w := 1, h := 2
    int lenWid = std::stoi(line[0]) * std::stoi(line[1]);
    int widHei = std::stoi(line[1]) * std::stoi(line[2]);
    int heiLen = std::stoi(line[2]) * std::stoi(line[0]);

    int surfaceArea = 2 * lenWid + 2 * widHei + 2 * heiLen +
                      std::min(std::min(lenWid, widHei), heiLen);

    result += surfaceArea;
    if (debug)
      std::cout << surfaceArea << "+";
  }

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_02.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, 'x');

  int result = 0;

  for (auto &&line : lines) {
    // l := 0, w := 1, h := 2
    std::vector<int> lineInt = {
        std::stoi(line[0]), std::stoi(line[1]), std::stoi(line[2])};
    std::sort(lineInt.begin(), lineInt.end());
    int wraping = 2 * lineInt[0] + 2 * lineInt[1];
    int bow = lineInt[0] * lineInt[1] * lineInt[2];

    int ribbonLength = wraping + bow;

    result += ribbonLength;
    if (debug)
      std::cout << ribbonLength << "+";
  }

  file.close();

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n"; // solution: 1586300
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution: 3737498
  return 0;
}