#include "../include/reader.h"
#include <cctype>
#include <iostream>

unsigned puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_03.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file);

  unsigned result = 0;
  std::string last;
  int multiplications = 0;  // Debug
  std::string beforeMult;   // Debug
  bool madeNewLine = false; // Debug

  int lineNumb = 1;
  for (auto &&line : lines) {
    bool multiply = false;

    for (auto &&character : line[0]) {
      beforeMult.push_back(character);
      // only append needed characters
      if (std::string{"mul0123456789,()"}.find_first_of(character) !=
          std::string::npos) {
        last.push_back(character);
      } else {
        multiply = false;
        last.clear();
      }
      // check for mul operation
      if (last.size() > 2 && last.rfind("mul") == (last.size() - 3)) {
        multiply = true;
        if (debug && !madeNewLine)
          std::cout << beforeMult;
        else if (debug)
          std::cout << lineNumb << "-" << multiplications << ": " << beforeMult;
        madeNewLine = false;
        last.clear();
        beforeMult.clear();
        continue;
      }
      // check multiplicants
      if (multiply && !last.empty() && last.front() == '(' &&
          last.back() == ')' && last.find(',') != std::string::npos) {
        multiply = false;
        madeNewLine = false;
        last.erase(last.begin());
        last.pop_back();
        std::vector<std::string> digits = seperate(last, ',');
        last.clear();
        beforeMult.clear();

        int first = 0;
        int second = 0;

        first = std::stoi(digits[0]);
        second = std::stoi(digits[1]);

        result += (first * second);
        ++multiplications;
        if (debug)
          std::cout << ":\t(" << first << "*" << second << ")\n";
        madeNewLine = true;
      }
    }
    ++lineNumb;
  }

  file.close();

  if (debug) {
    std::cout << "Number of mult: " << multiplications << "\n";
    std::cout << "Final result: ";
  }
  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_03.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file);

  unsigned result = 0;
  std::string last;
  bool toDo = true;
  int multiplications = 0;  // Debug
  std::string beforeMult;   // Debug
  bool madeNewLine = false; // Debug

  int lineNumb = 1;
  for (auto &&line : lines) {
    bool multiply = false;

    for (auto &&character : line[0]) {
      beforeMult.push_back(character);
      // only append needed characters
      if (std::string{"mul(,)don't0123456789"}.find_first_of(character) !=
          std::string::npos) {
        last.push_back(character);
      } else {
        multiply = false;
        last.clear();
      }
      // check for mul operation
      if (last.size() > 3 && last.rfind("do()") == (last.size() - 4))
        toDo = true;
      else if (last.size() > 6 && last.rfind("don't()") == (last.size() - 7))
        toDo = false;

      if (toDo && last.size() > 2 && last.rfind("mul") == (last.size() - 3)) {
        multiply = true;
        if (debug && !madeNewLine)
          std::cout << beforeMult;
        else if (debug)
          std::cout << lineNumb << "-" << multiplications << ": " << beforeMult;
        madeNewLine = false;
        last.clear();
        beforeMult.clear();
        continue;
      }
      // check multiplicants
      if (multiply && !last.empty() && last.front() == '(' &&
          last.back() == ')' && last.find(',') != std::string::npos) {
        multiply = false;
        madeNewLine = false;
        last.erase(last.begin());
        last.pop_back();
        std::vector<std::string> digits = seperate(last, ',');
        last.clear();
        beforeMult.clear();

        int first = 0;
        int second = 0;

        first = std::stoi(digits[0]);
        second = std::stoi(digits[1]);

        result += (first * second);
        ++multiplications;
        if (debug)
          std::cout << ":\t(" << first << "*" << second << ")\n";
        madeNewLine = true;
      }
    }
    ++lineNumb;
  }

  file.close();

  if (debug) {
    std::cout << "Number of mult: " << multiplications << "\n";
    std::cout << "Final result: ";
  }
  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n"; // solution: 155_955_228
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution:
  return 0;
}