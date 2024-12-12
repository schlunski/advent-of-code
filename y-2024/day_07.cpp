#include "../include/reader.h"
#include <bitset>
#include <cmath>
#include <iostream>

std::string toNumericalSystem(unsigned long long n, unsigned long long base) {
  std::string convertString = "0123456789ABCDEF";
  if (n < base) {
    return std::string(
        1, convertString[n]); // converts char to string, and returns it
  } else {
    return toNumericalSystem(n / base, base) +
           convertString[n % base]; // function makes a recursive call to
                                    // itself.
  }
}

unsigned long long puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_07.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ':');

  unsigned long long result = 0;
  int lineNumb = 0;
  for (auto line : lines) {
    trim(line[1], ' ');
    std::vector<std::string> numbers = seperate(line[1], ' ');

    unsigned long long counter = 0;
    if (debug)
      std::cout << "Check possibilities for Line " << lineNumb + 1 << ":\n";
    while (counter < std::pow(2, numbers.size())) {
      std::bitset<64> op{counter};
      std::string possibleWay = line[0] + " = " + numbers[0];
      unsigned long long lineResult = std::stoull(numbers[0]);
      for (int i = 1; i < numbers.size(); i++) {
        if (op[i - 1]) {
          lineResult *= std::stoull(numbers[i]);

          if (debug)
            possibleWay = possibleWay + " * " + numbers[i];
        } else {
          lineResult += std::stoull(numbers[i]);

          if (debug)
            possibleWay = possibleWay + " + " + numbers[i];
        }
      }
      if (lineResult == std::stoull(line[0])) {
        result += lineResult;

        if (debug)
          std::cout << possibleWay << "\n";
        break;
      }

      ++counter;
    }
    ++lineNumb;
  }

  file.close();

  return result;
}

unsigned long long puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_07.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ':');

  unsigned long long result = 0;
  int lineNumb = 0;
  for (auto line : lines) {
    trim(line[1], ' ');
    std::vector<std::string> numbers = seperate(line[1], ' ');

    unsigned long long counter = 0;
    if (debug)
      std::cout << "Check possibilities for Line " << lineNumb + 1 << ":\n";
    while (counter < std::pow(3, numbers.size() - 1)) {
      std::string op = toNumericalSystem(counter, 3);
      for (int i = 0; i < 41 - op.size(); i++) {
        op.insert(op.begin(), '0');
      }

      unsigned long long lineResult = std::stoull(numbers[0]);
      std::string possibleWay = line[0] + " = " + numbers[0];
      for (int i = 1; i < numbers.size(); i++) {
        switch (op[op.size() - i]) {
        case '0':
          lineResult *= std::stoull(numbers[i]);

          if (debug)
            possibleWay = possibleWay + " * " + numbers[i];
          break;
        case '1':
          lineResult += std::stoull(numbers[i]);

          if (debug)
            possibleWay = possibleWay + " + " + numbers[i];
          break;
        case '2':
          std::string res = std::to_string(lineResult) + numbers[i];
          lineResult = std::stoull(res);

          if (debug)
            possibleWay = possibleWay + " || " + numbers[i];
          break;
        }
      }
      if (lineResult == std::stoull(line[0])) {
        result += lineResult;
        if (debug)
          std::cout << possibleWay << "\n";
        break;
      }

      ++counter;
    }
    ++lineNumb;
  }

  file.close();

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 3119088655389
  std::cout << "Result Puzzle 2: " << puzzle_two(debug)
            << "\n"; // solution: 264184041398847
  return 0;
}