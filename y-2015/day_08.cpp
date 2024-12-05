#include "../include/reader.h"
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_08.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines = readFullFile(file, '\\');

  int code = 0;
  int memory = 0;
  int lineNumb = 0;
  bool lastEmpty = false;
  for (auto line : lines) {
    memory -= 2;
    code += line.size() - 1;
    int codeOnLine = line.size() - 1;
    int memoryOnLine = -2;
    for (auto word : line) {
      // for hexdecimal
      if (word.front() == 'x' && !lastEmpty) {
        memory -= 2;
        memoryOnLine -= 2;
      }
      // for backslash
      if (word.empty()) {
        ++memory;
        ++memoryOnLine;
        lastEmpty = true;
        continue;
      }
      lastEmpty = false;
      code += word.size();
      memory += word.size();
      codeOnLine += word.size();
      memoryOnLine += word.size();
    }
    if (debug) {
      std::cout << lineNumb << ": Code: " << codeOnLine
                << ", Mem: " << memoryOnLine << "\t";
      for (int i = 0; i < line.size(); ++i) {
        std::cout << line[i] << ((i < line.size() - 1) ? "\\" : " ");
      }
      std::cout << "\n";
    }
    ++lineNumb;
  }

  file.close();
  if (debug)
    std::cout << code << " - " << memory << " = ";

  return code - memory;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_08.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines = readFullFile(file);

  int code = 0;
  int memory = 0;
  int lineNumb = 0;
  bool lastEmpty = false;
  for (auto line : lines) {
    bool escape = false; 
    int hex = 0;
    for (auto character : line[0]) {
      if (!escape && character == '\\') {
        ++code;
        escape = true;
        hex = 0;
        continue;
      }

      if (!escape && character == '"') {
        ++code;
      } else if (escape && character == 'x') {
        ++code;
        ++memory;
      } else if (escape && hex < 2) {
        ++code;
        ++hex;
      } else {
        ++code;
        ++memory;
        escape = false;
      }
    }
    ++lineNumb;
  }

  file.close();
  if (debug)
    std::cout << code << " - " << memory << " = ";

  return code - memory;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug) << "\n"; // solution:
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution:
  return 0;
}