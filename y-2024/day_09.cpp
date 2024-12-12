#include "../include/reader.h"
#include <iostream>

unsigned long long puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_09.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::string> line = read_line<std::string>(file);
  file.close();

  // convert to int vector
  std::vector<int> filesystem;
  bool freeSpace = false;
  int id = 0;
  if (debug)
    std::cout << "Input:\n";
  for (auto character : line[0]) {
    for (int i = 0; i < std::stoi(std::string{character}); i++) {
      if (freeSpace) {
        filesystem.push_back(-1);

        if (debug)
          std::cout << '.';
      } else {
        filesystem.push_back(id);

        if (debug)
          std::cout << id;
      }
    }
    if (!freeSpace)
      ++id;
    freeSpace = !freeSpace;
  }
  if (debug)
    std::cout << "\n";

  unsigned long long result = 0;
  int posFromBack = filesystem.size() - 1;
  if (debug)
    std::cout << "nResult Puzzle 1: 0";
  for (int pos = 0; pos < filesystem.size(); ++pos) {
    while (filesystem[posFromBack] == -1) {
      --posFromBack;
    }
    if (pos > posFromBack)
      break;

    if (filesystem[pos] == -1) {
      filesystem[pos] = filesystem[posFromBack];
      filesystem[posFromBack] = -1;
      --posFromBack;
    }
    result += (filesystem[pos] * pos);
    if (debug)
      std::cout << " + " << filesystem[pos] * pos;
  }
  if (debug)
    std::cout << "\nResult Puzzle 1: ";

  return result;
}

unsigned long long puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_09.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::string> line = read_line<std::string>(file);
  file.close();

  // convert to vector with digit and length
  std::vector<std::pair<int, int>> filesystem;
  bool freeSpace = false;
  int id = 0;
  for (auto character : line[0]) {
    if (freeSpace) {
      filesystem.push_back({-1, std::stoi(std::string{character})});
    } else {
      filesystem.push_back({id, std::stoi(std::string{character})});
    }

    if (!freeSpace)
      ++id;
    freeSpace = !freeSpace;
  }

  if (debug) {
    std::cout << "Input: ";
    for (auto &&[number, length] : filesystem) {
      for (size_t i = 0; i < length; i++) {
        if (number == -1)
          std::cout << '.';
        else
          std::cout << number;
      }
    }
    std::cout << "\n";
  }
  unsigned long long result = 0;
  int left = 0;
  if (debug)
    std::cout << "Result Puzzle 2: ";
  for (int right = filesystem.size() - 1; right > -1; --right) {
    if (filesystem[right].first == -1)
      continue;

    for (size_t left = 0; left < filesystem.size(); ++left) {
      if (left >= right)
        break;
      if (filesystem[left].first != -1)
        continue;

      if (filesystem[right].second <= filesystem[left].second) {
        filesystem[left].first = filesystem[right].first;
        if (filesystem[right].second < filesystem[left].second) {
          filesystem.insert(
              filesystem.begin() + left + 1,
              {-1, filesystem[left].second - filesystem[right].second});
          ++right;
        }
        filesystem[left].second = filesystem[right].second;

        filesystem[right].first = -1;
        break;
      }
    }
  }

  if (debug) {
    for (auto [number, length] : filesystem) {
      for (size_t i = 0; i < length; i++) {
        if (number == -1)
          std::cout << '.';
        else
          std::cout << number;
      }
    }

    std::cout << "\nResult Puzzle 2: 0";
  }
  int pos = -1;
  for (auto [number, length] : filesystem) {
    for (size_t i = 0; i < length; i++) {
      ++pos;
      if (number == -1)
        continue;
      result += (number * pos);
      if (debug)
        std::cout << " + " << number * pos;
    }
  }
  if (debug)
    std::cout << "\n";
  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 6382875730645
  std::cout << "Result Puzzle 2: " << puzzle_two(debug)
            << "\n"; // solution: 6420913943576
  return 0;
}