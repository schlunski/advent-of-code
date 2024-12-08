#include "../include/reader.h"
#include <algorithm>
#include <iostream>

int puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_08.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines = readFullFile(file);
  file.close();

  // 2 dimensional vector with char and  bool if antidode on location
  std::vector<std::vector<std::pair<char, bool>>> map;
  for (int lineNumb = 0; lineNumb < lines.size(); ++lineNumb) {
    map.push_back({});
    for (auto &&character : lines[lineNumb][0]) {
      map[lineNumb].push_back({character, false});
    }
  }

  int result = 0;
  int lineNumb = 0;
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].size(); ++x) {
      // already checked
      if (map[y][x].first == '.' || map[y][x].first == '#')
        continue;

      if (debug)
        std::cout << "\tCheck " << map[y][x].first << "-frequency on location {"
                  << y << "," << x << "}:\n";
      // Check other Locations
      for (int yOther = y; yOther < map.size(); ++yOther) {
        for (int xOther = 0; xOther < map[yOther].size(); ++xOther) {
          if (!(y == yOther && x == xOther) &&
              map[y][x].first == map[yOther][xOther].first) {
            int xDistance = xOther - x;
            int yDistance = yOther - y;

            std::pair<int, int> antinodeOne{y - yDistance, x - xDistance};
            if (antinodeOne.first >= 0 && antinodeOne.first < map.size() &&
                antinodeOne.second >= 0 &&
                antinodeOne.second < map[antinodeOne.first].size()) {
              if (!map[antinodeOne.first][antinodeOne.second].second) {
                if (map[antinodeOne.first][antinodeOne.second].first == '.')
                  map[antinodeOne.first][antinodeOne.second].first = '#';
                map[antinodeOne.first][antinodeOne.second].second = true;
                ++result;

                if (debug)
                  std::cout << map[y][x].first << " Antinonde on: {"
                            << antinodeOne.first << "," << antinodeOne.second
                            << "}\n";
              } else if (debug) {
                std::cout << "Already taken on {" << antinodeOne.first << ","
                          << antinodeOne.second << "}\n";
              }
            } else if (debug) {
              std::cout << "OUT OF BOUNDS: {" << antinodeOne.first << ","
                        << antinodeOne.second << "}\n";
            }

            std::pair<int, int> antinodeTwo{
                yOther + yDistance, xOther + xDistance};
            if (antinodeTwo.first >= 0 && antinodeTwo.first < map.size() &&
                antinodeTwo.second >= 0 &&
                antinodeTwo.second < map[antinodeTwo.first].size()) {
              if (!map[antinodeTwo.first][antinodeTwo.second].second) {
                if (map[antinodeTwo.first][antinodeTwo.second].first == '.')
                  map[antinodeTwo.first][antinodeTwo.second].first = '#';
                map[antinodeTwo.first][antinodeTwo.second].second = true;
                ++result;
                if (debug)
                  std::cout << map[y][x].first << " Antinonde on: {"
                            << antinodeTwo.first << "," << antinodeTwo.second
                            << "}\n";
              } else if (debug) {
                std::cout << "Already taken on {" << antinodeTwo.first << ","
                          << antinodeTwo.second << "}\n";
              }
            } else if (debug) {
              std::cout << "OUT OF BOUNDS: {" << antinodeTwo.first << ","
                        << antinodeTwo.second << "}\n";
            }
          }
        }
      }
    }

    ++lineNumb;
  }

  if (debug) {
    std::cout << "Finished Map:\n";
    for (auto &&line : map) {
      for (auto &&pair : line) {
        std::cout << pair.first;
      }
      std::cout << "\n";
    }
  }

  return result;
}

int puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_08.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::vector<std::vector<std::string>> lines = readFullFile(file);
  file.close();

  // 2 dimensional vector with char and  bool if antidode on location
  std::vector<std::vector<std::pair<char, bool>>> map;
  for (int lineNumb = 0; lineNumb < lines.size(); ++lineNumb) {
    map.push_back({});
    for (auto &&character : lines[lineNumb][0]) {
      map[lineNumb].push_back({character, false});
    }
  }

  int result = 0;
  int lineNumb = 0;
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].size(); ++x) {
      // already checked
      if (map[y][x].first == '.' || map[y][x].first == '#')
        continue;

      if (debug)
        std::cout << "\tCheck " << map[y][x].first << "-frequency on location {"
                  << y << "," << x << "}:\n";
      // Check other Locations
      for (int yOther = y; yOther < map.size(); ++yOther) {
        for (int xOther = 0; xOther < map[yOther].size(); ++xOther) {
          if (!(y == yOther && x == xOther) &&
              map[y][x].first == map[yOther][xOther].first) {
            // Set antenna true
            if (!map[y][x].second) {
              map[y][x].second = true;
              ++result;
            }

            if (!map[yOther][xOther].second) {
              map[yOther][xOther].second = true;
              ++result;
            }

            int xDistance = xOther - x;
            int yDistance = yOther - y;

            int multiplier = 1;
            bool outOfBounds = false;
            while (!outOfBounds) {
              std::pair<int, int> antinodeOne{
                  y - multiplier * yDistance, x - multiplier * xDistance};
              if (antinodeOne.first >= 0 && antinodeOne.first < map.size() &&
                  antinodeOne.second >= 0 &&
                  antinodeOne.second < map[antinodeOne.first].size()) {
                if (!map[antinodeOne.first][antinodeOne.second].second) {
                  if (map[antinodeOne.first][antinodeOne.second].first == '.')
                    map[antinodeOne.first][antinodeOne.second].first = '#';
                  map[antinodeOne.first][antinodeOne.second].second = true;
                  ++result;

                  if (debug)
                    std::cout << map[y][x].first << " Antinonde on: {"
                              << antinodeOne.first << "," << antinodeOne.second
                              << "}\n";
                } else if (debug) {
                  std::cout << "Already taken on {" << antinodeOne.first << ","
                            << antinodeOne.second << "}\n";
                }
                ++multiplier;
              } else {
                outOfBounds = true;

                if (debug)
                  std::cout << "OUT OF BOUNDS: {" << antinodeOne.first << ","
                            << antinodeOne.second << "}\n";
              }
            }

            multiplier = 1;
            outOfBounds = false;
            while (!outOfBounds) {
              std::pair<int, int> antinodeTwo{
                  yOther + multiplier * yDistance,
                  xOther + multiplier * xDistance};
              if (antinodeTwo.first >= 0 && antinodeTwo.first < map.size() &&
                  antinodeTwo.second >= 0 &&
                  antinodeTwo.second < map[antinodeTwo.first].size()) {
                if (!map[antinodeTwo.first][antinodeTwo.second].second) {
                  if (map[antinodeTwo.first][antinodeTwo.second].first == '.')
                    map[antinodeTwo.first][antinodeTwo.second].first = '#';
                  map[antinodeTwo.first][antinodeTwo.second].second = true;
                  ++result;
                  if (debug)
                    std::cout << map[y][x].first << " Antinonde on: {"
                              << antinodeTwo.first << "," << antinodeTwo.second
                              << "}\n";
                } else if (debug) {
                  std::cout << "Already taken on {" << antinodeTwo.first << ","
                            << antinodeTwo.second << "}\n";
                }
                ++multiplier;
              } else {
                outOfBounds = true;

                if (debug)
                  std::cout << "OUT OF BOUNDS: {" << antinodeTwo.first << ","
                            << antinodeTwo.second << "}\n";
              }
            }
          }
        }
      }
    }

    ++lineNumb;
  }

  if (debug) {
    std::cout << "Finished Map:\n";
    for (auto &&line : map) {
      for (auto &&pair : line) {
        std::cout << pair.first;
      }
      std::cout << "\n";
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 423
  std::cout << "Result Puzzle 2: " << puzzle_two(debug)
            << "\n"; // solution: 1287
  return 0;
}