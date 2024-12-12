#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>

// Recursive pathfinding fuction
int count_paths(
    bool part1, const std::vector<std::vector<int>> &map,
    std::pair<int, int> startPos, std::pair<int, int> currPos,
    std::map<std::pair<int, int>, std::set<std::pair<int, int>>>
        &alreadyChecked) {
  // Break for rekursion
  if (map[currPos.first][currPos.second] == 9) {
    if (alreadyChecked.find(startPos) != alreadyChecked.end()) {
      if (part1 && alreadyChecked[startPos].find(currPos) !=
                       alreadyChecked[startPos].end()) {
        return 0;
      }

      alreadyChecked[startPos].insert(currPos);
      return 1;
    }

    alreadyChecked.insert({startPos, {currPos}});
    return 1;
  }

  int paths = 0;
  std::vector<std::vector<int>> copyMap;
  // check North
  if (currPos.first - 1 >= 0 && map[currPos.first - 1][currPos.second] ==
                                    map[currPos.first][currPos.second] + 1) {
    copyMap = map;
    copyMap[currPos.first][currPos.second] = -1;
    paths += count_paths(
        part1, copyMap, startPos, {currPos.first - 1, currPos.second},
        alreadyChecked);
  }
  // check South
  if (currPos.first + 1 < map.size() &&
      map[currPos.first + 1][currPos.second] ==
          map[currPos.first][currPos.second] + 1) {
    copyMap = map;
    copyMap[currPos.first][currPos.second] = -1;
    paths += count_paths(
        part1, copyMap, startPos, {currPos.first + 1, currPos.second},
        alreadyChecked);
  }
  // check West
  if (currPos.second - 1 >= 0 && map[currPos.first][currPos.second - 1] ==
                                     map[currPos.first][currPos.second] + 1) {
    copyMap = map;
    copyMap[currPos.first][currPos.second] = -1;
    paths += count_paths(
        part1, copyMap, startPos, {currPos.first, currPos.second - 1},
        alreadyChecked);
  }
  // check East
  if (currPos.second + 1 < map[currPos.first].size() &&
      map[currPos.first][currPos.second + 1] ==
          map[currPos.first][currPos.second] + 1) {

    copyMap = map;
    copyMap[currPos.first][currPos.second] = -1;
    paths += count_paths(
        part1, copyMap, startPos, {currPos.first, currPos.second + 1},
        alreadyChecked);
  }
  return paths;
}

int puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_10.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file);
  file.close();
  // Conver to int map
  std::vector<std::vector<int>> map;
  for (auto line : lines) {
    map.push_back({});
    for (auto number : line[0]) {
      map[map.size() - 1].push_back(int(number - '0'));
    }
  }

  int result = 0;
  std::map<std::pair<int, int>, std::set<std::pair<int, int>>>
      alreadyCheckedPaths;
  for (size_t y = 0; y < map.size(); y++) {
    for (size_t x = 0; x < map[y].size(); x++) {
      if (map[y][x] != 0)
        continue;

      result += count_paths(true, map, {y, x}, {y, x}, alreadyCheckedPaths);
    }
  }

  if (debug) {
    std::cout << "All possible paths:\n";
    for (auto &&[start, ends] : alreadyCheckedPaths) {
      std::cout << "Start: {" << start.first << "," << start.second << "} has "
                << ends.size() << " possible Paths to: ";
      for (auto &&end : ends) {
        std::cout << "{" << end.first << "," << end.second << "}, ";
      }
      std::cout << "\n";
    }
    std::cout << "Number of possible paths: ";
  }

  return result;
}

int puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_10.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file);
  file.close();
  // Conver to int map
  std::vector<std::vector<int>> map;
  for (auto line : lines) {
    map.push_back({});
    for (auto number : line[0]) {
      map[map.size() - 1].push_back(int(number - '0'));
    }
  }

  int result = 0;
  std::map<std::pair<int, int>, std::set<std::pair<int, int>>>
      alreadyCheckedPaths;
  for (size_t y = 0; y < map.size(); y++) {
    for (size_t x = 0; x < map[y].size(); x++) {
      if (map[y][x] != 0)
        continue;

      result += count_paths(false, map, {y, x}, {y, x}, alreadyCheckedPaths);
    }
  }

  if (debug) {
    std::cout << "All possible paths:\n";
    for (auto &&[start, ends] : alreadyCheckedPaths) {
      std::cout << "Start: {" << start.first << "," << start.second << "} has "
                << ends.size() << " possible Paths to: ";
      for (auto &&end : ends) {
        std::cout << "{" << end.first << "," << end.second << "}, ";
      }
      std::cout << "\n";
    }
    std::cout << "Number of possible paths: ";
  }

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 496
  std::cout << "Result Puzzle 2: " << puzzle_two(debug)
            << "\n"; // solution: 1120
  return 0;
}