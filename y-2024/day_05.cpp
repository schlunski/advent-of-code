#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_05.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, '|');
  std::map<std::string, std::vector<std::string>> pageRules;

  int result = 0;
  int lineNumb = 0;
  // go through lines and add page rules to map
  for (auto &&line : lines) {
    if (line.size() < 2)
      break;

    if (pageRules.find(line[0]) == pageRules.end()) {
      pageRules.insert({line[0], {}});
    }
    pageRules[line[0]].push_back(line[1]);

    ++lineNumb;
  }

  if (debug)
    std::cout << "Map extracted with " << pageRules.size() << " entries\n";

  // skip empty line
  ++lineNumb;

  // check updates
  if (debug)
    std::cout << "Checkin Updates:\n";
  for (int updateNumber = lineNumb; updateNumber < lines.size();
       updateNumber++) {
    bool incorrect = false;
    std::vector<std::string> pages = seperate(lines[lineNumb][0], ',');
    for (int i = pages.size() - 1; i > 0; --i) {
      for (int j = i - 1; j >= 0; --j) {

        if (std::find(
                pageRules[pages[i]].begin(), pageRules[pages[i]].end(),
                pages[j]) != pageRules[pages[i]].end()) {
          incorrect = true;
          break;
        }
        if (incorrect)
          break;
      }
      if (incorrect)
        break;
    }

    if (!incorrect) {
      if (debug)
        std::cout << "Line " << lineNumb + 1 << ": "
                  << std::stoi(pages[int(pages.size() / 2)]) << "\n";
      result += std::stoi(pages[int(pages.size() / 2)]);
    }

    ++lineNumb;
  }

  file.close();

  if (debug)
    std::cout << "Result Puzzle 1: ";

  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_05.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, '|');
  std::map<std::string, std::vector<std::string>> pageRules;

  int result = 0;
  int lineNumb = 0;
  // go through lines and add page rules to map
  for (auto &&line : lines) {
    if (line.size() < 2)
      break;

    if (pageRules.find(line[0]) == pageRules.end()) {
      pageRules.insert({line[0], {}});
    }
    pageRules[line[0]].push_back(line[1]);

    ++lineNumb;
  }

  if (debug)
    std::cout << "Map extracted with " << pageRules.size() << " entries\n";

  // skip empty line
  ++lineNumb;

  // check updates
  for (int updateNumber = lineNumb; updateNumber < lines.size();
       updateNumber++) {
    bool incorrect = false;
    std::vector<std::string> pages = seperate(lines[lineNumb][0], ',');
    for (int i = pages.size() - 1; i > 0; --i) {
      for (int j = i - 1; j >= 0; --j) {

        if (std::find(
                pageRules[pages[i]].begin(), pageRules[pages[i]].end(),
                pages[j]) != pageRules[pages[i]].end()) {
          incorrect = true;
          break;
        }
        if (incorrect)
          break;
      }
      if (incorrect)
        break;
    }

    if (incorrect) {
      // Sorting to right order
      std::vector<std::string> orderedPages = {pages[0]};
      for (int i = 1; i < pages.size(); ++i) {
        bool hadBreake = false;
        for (int j = 0; j < orderedPages.size(); ++j) {
          if (std::find(
                  pageRules[pages[i]].begin(), pageRules[pages[i]].end(),
                  orderedPages[j]) != pageRules[pages[i]].end()) {
            orderedPages.insert(orderedPages.begin() + j, pages[i]);
            hadBreake = true;
            break;
          }
        }
        if (!hadBreake)
          orderedPages.push_back(pages[i]);
      }
      if (debug) {
        std::cout << "Line " << lineNumb + 1 << "-";
        std::cout << "{";
        for (auto &&page : orderedPages) {
          std::cout << page << ",";
        }
        std::cout << "}: "
                  << std::stoi(orderedPages[int(orderedPages.size() / 2)])
                  << "\n";
      }
      result += std::stoi(orderedPages[int(orderedPages.size() / 2)]);
    }

    ++lineNumb;
  }

  file.close();

  if (debug)
    std::cout << "Result Puzzle 2: ";

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug)
            << "\n\n"; // solution: 6242
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug)
            << "\n"; // solution: 5169
  return 0;
}