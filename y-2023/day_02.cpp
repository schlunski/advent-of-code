#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>

int puzzleOne(bool debug = false) {
  std::map<std::string, int> maxCubes = {
      {"red", 12}, {"green", 13}, {"blue", 14}};
  std::fstream file("puzzle-inputs/input_02.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file);

  int result = 0;

  std::vector<std::string> games;
  for (auto &&line : lines) {
    games.push_back(seperate(line[0], ':')[1]);
  }

  int gameID = 1;
  for (auto &&game : games) {
    bool possible = true;
    // look at one set at a time
    for (auto &&set : seperate(game, ';')) {
      trim(set, ' ');
      // check the revealed cubes
      for (auto &&cubesWithColor : seperate(set, ',')) {
        trim(cubesWithColor, ' ');
        // compare revealed with maximum
        if (std::stoi(seperate(cubesWithColor, ' ')[0]) >
            maxCubes.at(seperate(cubesWithColor, ' ')[1])) {
          possible = false;
          break;
        }
      }

      if (!possible)
        break;
    }

    if (possible) {
      if (debug)
        std::cout << gameID << "+";
      result += gameID;
    }

    ++gameID;
  }
  if (debug)
    std::cout << " = " << result << "\n";

  file.close();

  return result;
}

int puzzleTwo(bool debug = false) {
  std::map<std::string, int> maxCubes = {
      {"red", 12}, {"green", 13}, {"blue", 14}};
  std::map<std::string, int> minCubes = {
      {"red", 0}, {"green", 0}, {"blue", 0}};

  std::fstream file("puzzle-inputs/input_02.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file);

  int result = 0;

  std::vector<std::string> games;
  for (auto &&line : lines) {
    games.push_back(seperate(line[0], ':')[1]);
  }

  for (auto &&game : games) {
    minCubes = {{"red", 0}, {"green", 0}, {"blue", 0}};
    // look at one set at a time
    for (auto &&set : seperate(game, ';')) {
      trim(set, ' ');
      // check the revealed cubes
      for (auto &&cubesWithColor : seperate(set, ',')) {
        trim(cubesWithColor, ' ');
        // compare revealed with maximum
        if (std::stoi(seperate(cubesWithColor, ' ')[0]) >
            minCubes.at(seperate(cubesWithColor, ' ')[1])) {
          minCubes[seperate(cubesWithColor, ' ')[1]] =
              std::stoi(seperate(cubesWithColor, ' ')[0]);
        }
      }
    }

    int powers = 1;
    for (auto &[color, cubes] : minCubes) {
      powers *= cubes;
    }
  
    if (debug)
      std::cout << powers << "+";
  
    result += powers;
  }
  
  if (debug)
    std::cout << "0 = " << result << "\n";

  file.close();

  return result;
}

int main() {
  std::cout << "Result Puzzle 1: " << puzzleOne() << "\n";
  std::cout << "Result Puzzle 2: "<< puzzleTwo() << "\n";
  return 0;
}