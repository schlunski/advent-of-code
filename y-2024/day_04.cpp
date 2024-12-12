#include "../include/reader.h"
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_04.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file);

  std::vector<std::string> accepted = {"XMAS", "SAMX"};
  int result = 0;

  for (int line = 0; line < lines.size(); ++line) {
    for (int i = 0; i < lines[line][0].size(); i++) {
      std::string word;
      // check vertical line
      if (line < lines.size() - 3) {
        word = lines[line][0][i];
        word.push_back(lines[line + 1][0][i]);
        word.push_back(lines[line + 2][0][i]);
        word.push_back(lines[line + 3][0][i]);
        if (word == accepted[0] || word == accepted[1]) {
          ++result;
          if (debug)
            std::cout << line + 1 << "-" << i + 1 << ": " << word << "\n";
        }

        // check diagonal right
        if (i < lines[line][0].size() - 3) {
          word = lines[line][0][i];
          word.push_back(lines[line + 1][0][i + 1]);
          word.push_back(lines[line + 2][0][i + 2]);
          word.push_back(lines[line + 3][0][i + 3]);
          if (word == accepted[0] || word == accepted[1]) {
            ++result;
            if (debug)
              std::cout << line + 1 << "-" << i + 1 << ": " << word << "\n";
          }
        }
        // check diagonal left
        if (i > 2) {
          word = lines[line][0][i];
          word.push_back(lines[line + 1][0][i - 1]);
          word.push_back(lines[line + 2][0][i - 2]);
          word.push_back(lines[line + 3][0][i - 3]);
          if (word == accepted[0] || word == accepted[1]) {
            ++result;
            if (debug)
              std::cout << line << "-" << i - 3 << ": " << word << "\n";
          }
        }
      }

      if (i > 2 && i < lines[line][0].size()) {
        // chek on same line
        word = lines[line][0].substr(i - 3, 4);
        if (word == accepted[0] || word == accepted[1]) {
          ++result;
          if (debug)
            std::cout << line + 1 << "-" << i - 3 << ": " << word << "\n";
        }
      }
    }
  }

  file.close();

  if (debug)
    std::cout << "Result Puzzle 1: ";
  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_04.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file);

  std::vector<std::string> accepted = {"MAS", "SAM"};
  int result = 0;

  for (int line = 1; line < lines.size() - 1; ++line) {
    if (debug)
      std::cout << "X-MAS on line " << line + 1 << ": ";

    for (int i = 1; i < lines[line][0].size() - 1; i++) {
      // check vertical line
      if (lines[line][0][i] == 'A') {
        // check diagonal right
        std::string word1 = std::string{lines[line - 1][0][i - 1]};
        word1.push_back(lines[line][0][i]);
        word1.push_back(lines[line + 1][0][i + 1]);
        // check diagonal left
        std::string word2 = std::string{lines[line - 1][0][i + 1]};
        word2.push_back(lines[line][0][i]);
        word2.push_back(lines[line + 1][0][i - 1]);
        if ((word1 == accepted[0] || word1 == accepted[1]) &&
            (word2 == accepted[0] || word2 == accepted[1])) {
          ++result;
          if (debug)
            std::cout << i << ", ";
        }
      }
    }
    if (debug)
      std::cout << "\n";
  }

  file.close();

  if (debug)
    std::cout << "Result Puzzle 2: ";
  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n"; // solution: 2521
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug)
            << "\n"; // solution: 1912
  return 0;
}