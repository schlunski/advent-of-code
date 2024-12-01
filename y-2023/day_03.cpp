#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>

int puzzleOne(bool debug = false) {
  std::fstream file("puzzle-inputs/input_03.txt");
  int result = 0;

  std::vector<std::vector<std::string>> linesvec = readFullFile(file);

  std::vector<std::string> lines;
  for (auto &&line : linesvec) {
    lines.push_back(line[0]);
  }

  int linenumb = 0;
  for (auto &&line : lines) {
    std::map<int, std::string> posWithNumber = {};
    std::string word;
    int pos = 0;

    if (debug)
      std::cout << "Numbers in the line " << linenumb + 1 << ":\n";
    // save numbers with their position
    for (auto &&character : line) {
      try {
        std::stoi(std::string{character});
        word.push_back(character);
      } catch (const std::exception &e) {
        if (!word.empty()) {
          posWithNumber.insert({pos - word.size(), word});
          if (debug)
            std::cout << "Pos&Word: {" << pos - word.size() << "," << word
                      << "} ";
          word.clear();
        }
      }
      ++pos;
    }
    if (debug)
      std::cout << "\nCheck line above:\n";
    
    std::set<int> alreadyAdded = {};

    int lineResult = 0;

    // check above
    if (linenumb - 1 >= 0) {
      for (auto &&[pos, number] : posWithNumber) {
        int min = (pos - 1 >= 0) ? pos - 1 : pos;
        int max = (pos + number.size() < line.size()) ? pos + number.size()
                                                      : line.size();
        for (int checkPos = min; checkPos <= max; ++checkPos) {
          if (alreadyAdded.find(pos) == alreadyAdded.end() &&
              lines[linenumb - 1][checkPos] != '.' &&
              std::string{"1234567890"}.find(lines[linenumb - 1][checkPos]) ==
                  std::string::npos) {
            if (debug)
              std::cout << std::stoi(number) << "+";
            result += std::stoi(number);
            lineResult += std::stoi(number);
            alreadyAdded.insert(pos);
            break;
          }
        }
      }
    }

    // remove already added number from checking
    for (auto pos : alreadyAdded) {
      posWithNumber.erase(pos);
    }
    alreadyAdded.clear();

    if (debug)
      std::cout << "\nCheck same line:\n";
    // check same line
    for (auto &&[pos, number] : posWithNumber) {
      if (pos - 1 >= 0) {
        // left side of number
        if (alreadyAdded.find(pos) == alreadyAdded.end() &&
            line[pos - 1] != '.' &&
            std::string{"1234567890"}.find(line[pos - 1]) ==
                std::string::npos) {
          if (debug)
            std::cout << std::stoi(number) << "+";
          result += std::stoi(number);
            lineResult += std::stoi(number);
          alreadyAdded.insert(pos);
          continue;
        }
      }
      // right side of number
      if (pos + number.size() < line.size()) {
        if (alreadyAdded.find(pos) == alreadyAdded.end() &&
            line[pos + number.size()] != '.' &&
            std::string{"1234567890"}.find(line[pos + number.size()]) ==
                std::string::npos) {
          if (debug)
            std::cout << std::stoi(number) << "+";
          result += std::stoi(number);
          lineResult += std::stoi(number);
          alreadyAdded.insert(pos);
        }
      }
    }

    // remove already added number from checking
    for (auto pos : alreadyAdded) {
      posWithNumber.erase(pos);
    }
    alreadyAdded.clear();

    if (debug)
      std::cout << "\nCheck line below:\n";
    // chek bellow
    if (linenumb + 1 < lines.size()) {
      for (auto &&[pos, number] : posWithNumber) {
        int min = (pos - 1 >= 0) ? pos - 1 : pos;
        int max = (pos + number.size() < line.size())
                      ? pos + number.size()
                      : line.size();
        for (int checkPos = min; checkPos <= max; ++checkPos) {
          if (alreadyAdded.find(pos) == alreadyAdded.end() &&
              lines[linenumb + 1][checkPos] != '.' &&
              std::string{"1234567890"}.find(lines[linenumb + 1][checkPos]) ==
                  std::string::npos) {
            if (debug)
              std::cout << std::stoi(number) << "+";
            result += std::stoi(number);
            lineResult += std::stoi(number);
            alreadyAdded.insert(pos);
            break;
          }
        }
      }
    }

    if (debug)
      std::cout << "\n\tLineresult: " << lineResult << "\n\t";

    ++linenumb;
  }

  if (debug)
    std::cout << " 0 = " << result << "\n";

  return result;
}

int puzzleTwo(bool debug = false) {
  std::fstream file("puzzle-inputs/input_03.txt");

  int result = 0;
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