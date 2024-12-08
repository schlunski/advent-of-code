#include "../include/reader.h"
#include <algorithm>
#include <iostream>

enum Direction { NORTH, EAST, SOUTH, WEST };

int puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_06.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines = readFullFile(file);

  Direction direction = NORTH;

  // find quard (x,y)
  std::pair<int, int> guardPosition = {-1, -1};
  int lineNumb = 0;
  for (auto &&line : lines) {
    guardPosition.first = line[0].find('^');
    guardPosition.second = lineNumb;
    if (guardPosition.first != std::string::npos)
      break;
    ++lineNumb;
  }

  int result = 0;
  lineNumb = 0;
  char charOnGuardPosition = '.';
  while ((direction == NORTH && guardPosition.second - 1 != -1) ||
         (direction == SOUTH && guardPosition.second + 1 != lines.size()) ||
         (direction == EAST &&
          guardPosition.first + 1 != lines[guardPosition.second][0].size()) ||
         (direction == WEST && guardPosition.first - 1 != -1)) {
    std::pair<int, int> newGuardPosition = guardPosition;
    switch (direction) {
    case NORTH:
      newGuardPosition.second -= 1;
      break;
    case SOUTH:
      newGuardPosition.second += 1;
      break;
    case EAST:
      newGuardPosition.first += 1;
      break;
    case WEST:
      newGuardPosition.first -= 1;
      break;
    }

    char *guardFront =
        &lines[newGuardPosition.second][0][newGuardPosition.first];
    if (*guardFront == '#') {
      if (debug)
        std::cout << "Direction change at: {" << newGuardPosition.first << ","
                  << newGuardPosition.second << "}\n";
      switch (direction) {
      case NORTH:
        direction = EAST;
        break;
      case EAST:
        direction = SOUTH;
        break;
      case SOUTH:
        direction = WEST;
        break;
      case WEST:
        direction = NORTH;
        break;
      }
      continue;
    }

    if (*guardFront == '.') {
      if (charOnGuardPosition == '.')
        ++result;
      charOnGuardPosition = '.';
      *guardFront = *"^";
    } else if (*guardFront == 'X') {
      if (charOnGuardPosition == '.')
        ++result;
      charOnGuardPosition = 'X';
      *guardFront = *"^";
    }
    lines[guardPosition.second][0][guardPosition.first] = 'X';
    guardPosition = newGuardPosition;
  }
  ++result;
  file.close();

  return result;
}

int puzzle_two_brute_force(bool debug) {
  std::fstream file("puzzle_inputs/input_06.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines = readFullFile(file);
  // Startdirection
  Direction direction = NORTH;

  std::vector<std::vector<std::pair<char, std::vector<Direction>>>> map;
  std::vector<std::vector<std::pair<char, std::vector<Direction>>>> resetMap;
  std::pair<int, int> guardPosition = {-1, -1};
  std::pair<int, int> resetGuardPosition;

  // find quard (x,y)
  int lineNumb = 0;
  for (auto line : lines) {
    map.push_back({});
    if (line[0].find('^') != std::string::npos) {
      guardPosition.first = line[0].find('^');
      guardPosition.second = lineNumb;
    }
    for (auto &&character : line[0]) {
      map[lineNumb].push_back({character, {}});
    }
    ++lineNumb;
  }

  resetMap = map;
  resetGuardPosition = guardPosition;
  std::vector<std::pair<int, int>> possibleObstacleLocations;

  int result = 0;
  lineNumb = 0;
  char newCharOnPos = '^';

  if (debug) {
    std::cout << "Startin map:\n";

    for (auto &&line : map) {
      for (auto &&[character, directions] : line) {
        std::cout << character;
      }
      std::cout << "\n";
    }
  }
  for (int y = 0; y < resetMap.size(); ++y) {
    for (int x = 0; x < resetMap[y].size(); x++) {
      guardPosition = resetGuardPosition;
      map = resetMap;
      direction = NORTH;
      if (map[y][x].first != '.')
        continue;
      else
        map[y][x].first = 'O';

      while ((direction == NORTH && guardPosition.second - 1 != -1) ||
             (direction == SOUTH && guardPosition.second + 1 != map.size()) ||
             (direction == EAST &&
              guardPosition.first + 1 != map[guardPosition.second].size()) ||
             (direction == WEST && guardPosition.first - 1 != -1)) {
        // Next position
        std::pair<int, int> newGuardPosition = guardPosition;
        switch (direction) {
        case NORTH:
          newGuardPosition.second -= 1;
          newCharOnPos = '|';
          break;
        case SOUTH:
          newGuardPosition.second += 1;
          newCharOnPos = '|';
          break;
        case EAST:
          newGuardPosition.first += 1;
          newCharOnPos = '-';
          break;
        case WEST:
          newGuardPosition.first -= 1;
          newCharOnPos = '-';
          break;
        }
        map[guardPosition.second][guardPosition.first].second.push_back(
            direction);

        if (std::find(
                map[newGuardPosition.second][newGuardPosition.first]
                    .second.begin(),
                map[newGuardPosition.second][newGuardPosition.first]
                    .second.end(),
                direction) !=
            map[newGuardPosition.second][newGuardPosition.first].second.end()) {
          ++result;
          possibleObstacleLocations.push_back({y, x});
          if (debug) {
            std::cout << "Possible for obstacle on - {" << y << "," << x
                      << "}:\n";

            for (auto &&line : map) {
              for (auto &&[character, directions] : line) {
                if (directions.size() > 1)
                  std::cout << '+';
                else
                  std::cout << character;
              }
              std::cout << "\n";
            }
          }

          break;
        }
        // direction change
        char *guardFront =
            &map[newGuardPosition.second][newGuardPosition.first].first;
        if (*guardFront == '#' || *guardFront == 'O') {
          switch (direction) {
          case NORTH:
            direction = EAST;
            break;
          case EAST:
            direction = SOUTH;
            break;
          case SOUTH:
            direction = WEST;
            break;
          case WEST:
            direction = NORTH;
            break;
          }
        } else {
          map[guardPosition.second][guardPosition.first].first = newCharOnPos;
          guardPosition = newGuardPosition;
        }
      }
    }
  }

  if (debug) {
    std::cout << "All possible locations for obstacles:\n";
    for (auto &&[y, x] : possibleObstacleLocations) {
      std::cout << "{" << y << "," << x << "}, ";
    }
    std::cout << "\nResult Puzzle 2: ";
  }

  file.close();

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 4977
  std::cout << "Result Puzzle 2: " << puzzle_two_brute_force(debug)
            << "\n"; // solution: 1729
  return 0;
}