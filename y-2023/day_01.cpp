#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>

int puzzleOne(bool debug = false) {
  std::fstream file("puzzle-inputs/input_01.txt");
  std::vector<std::vector<std::string>> lines =
      readFullFile(file, '\0', 0, false);

  int result = 0;
  std::string lineresult;

  for (auto line : lines) {
    lineresult = "";
    // first number
    for (auto character : line[0]) {
      if (0 < int(character - '0') && int(character - '0') < 10) {
        lineresult.push_back(character);
        break;
      }
    }
    // last number
    std::reverse(line[0].begin(), line[0].end());
    for (auto character : line[0]) {
      if (0 < int(character - '0') && int(character - '0') < 10) {
        lineresult.push_back(character);
        break;
      }
    }
    if (debug)
      std::cout << lineresult << "+";

    result += std::stoi(lineresult);
  }

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int puzzleTwo(bool debug = false) {
  std::fstream file("puzzle-inputs/input_01.txt");
  std::vector<std::vector<std::string>> lines =
      readFullFile(file, '\0', 0, false);

  std::map<char, std::string> possibleNumbers = {
      {'1', "one"},   {'2', "two"},   {'3', "three"},
      {'4', "four"},  {'5', "five"},  {'6', "six"},
      {'7', "seven"}, {'8', "eight"}, {'9', "nine"}};

  int result = 0;
  std::string lineresult;
  std::string numb;
  bool nextline;
  for (auto line : lines) {
    numb.clear();
    lineresult = "";
    // first number
    for (auto character : line[0]) {
      numb.push_back(character);
      nextline = false;
      // check for number in text
      for (auto &[key, number] : possibleNumbers) {
        if (numb.size() >= number.size() &&
            numb.compare(numb.size() - number.size(), number.size(), number) ==
                0) {
          lineresult.push_back(key);
          nextline = true;
          break;
        }
      }
      // number found in text
      if (nextline)
        break;
      
      if (0 < int(character - '0') && int(character - '0') < 10) {
        lineresult.push_back(character);
        break;
      }
    }
    // last number
    numb.clear();
    std::reverse(line[0].begin(), line[0].end());
    for (auto character : line[0]) {
      numb.push_back(character);
      nextline = false;
      // check for number in text
      for (auto &[key, number] : possibleNumbers) {
        std::reverse(number.begin(), number.end());

        if (numb.size() >= number.size() &&
            numb.compare(numb.size() - number.size(), number.size(), number) ==
                0) {
          lineresult.push_back(key);
          nextline = true;
          std::reverse(number.begin(), number.end());
          break;
        }
        std::reverse(number.begin(), number.end());
      }
      // number found in text
      if (nextline)
        break;
      
      if (0 < int(character - '0') && int(character - '0') < 10) {
        lineresult.push_back(character);
        break;
      }
    }
    if (debug)
      std::cout << lineresult << "+";

    result += std::stoi(lineresult);
  }

  if (debug)
    std::cout << "0 = " << result << "\n";

  return result;
}

int main() {
  // std::cout << puzzleOne() << "\n";

  std::cout << puzzleTwo(true) << "\n";

  return 0;
}