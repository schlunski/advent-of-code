#include "../include/reader.h"
#include <iostream>
#include <set>

int puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_15.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::pair<unsigned, unsigned> pos(0, 0);

  // get the map
  std::vector<std::vector<char>> map;
  std::vector<char> line = read_line<char>(file);
  while (line.size() > 0) {
    map.push_back({});
    for (int i = 0; i < line.size(); i++) {
      map[map.size() - 1].push_back(line[i]);
      if (line[i] == '@') {
        pos.first = map.size() - 1;
        pos.second = i;
      }
    }
    line = read_line<char>(file);
  }

  // get the movement
  std::vector<char> movement;
  line = read_line<char>(file);
  while (line.size() > 0) {
    for (auto move : line) {
      movement.push_back(move);
    }
    line = read_line<char>(file);
  }
  file.close();

  for (auto move : movement) {
    int endPos = -1;
    switch (move) {
    case '<':
      for (int x = pos.second - 1; x >= 0; --x) {
        if (map[pos.first][x] == '#') {
          endPos = -1;
          break;
        } else if (map[pos.first][x] == '.') {
          endPos = x;
          break;
        }
      }
      if (endPos != -1) {
        for (int x = endPos; x < pos.second; ++x) {
          map[pos.first][x] = map[pos.first][x + 1];
        }
        map[pos.first][pos.second] = '.';
        --pos.second;
      }
      break;
    case '>':
      for (int x = pos.second + 1; x < map[pos.first].size(); ++x) {
        if (map[pos.first][x] == '#') {
          endPos = -1;
          break;
        } else if (map[pos.first][x] == '.') {
          endPos = x;
          break;
        }
      }
      if (endPos != -1) {
        for (int x = endPos; x > pos.second; --x) {
          map[pos.first][x] = map[pos.first][x - 1];
        }
        map[pos.first][pos.second] = '.';
        ++pos.second;
      }
      break;
    case '^':
      for (int y = pos.first - 1; y >= 0; --y) {
        if (map[y][pos.second] == '#') {
          endPos = -1;
          break;
        } else if (map[y][pos.second] == '.') {
          endPos = y;
          break;
        }
      }
      if (endPos != -1) {
        for (int y = endPos; y < pos.first; ++y) {
          map[y][pos.second] = map[y + 1][pos.second];
        }
        map[pos.first][pos.second] = '.';
        --pos.first;
      }
      break;
    case 'v':
      for (int y = pos.first + 1; y < map.size(); ++y) {
        if (map[y][pos.second] == '#') {
          endPos = -1;
          break;
        } else if (map[y][pos.second] == '.') {
          endPos = y;
          break;
        }
      }
      if (endPos != -1) {
        for (int y = endPos; y > pos.first; --y) {
          map[y][pos.second] = map[y - 1][pos.second];
        }
        map[pos.first][pos.second] = '.';
        ++pos.first;
      }
      break;
    }

    if (debug) {
      printf("Move %c:\n", move);
      for (auto &&line : map) {
        for (auto &&character : line) {
          printf("%c", character);
        }
        printf("\n");
      }
      printf("\n");
    }
  }

  // calculate result for boxes
  int result = 0;
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].size(); ++x) {
      if (map[y][x] == 'O') {
        result += 100 * y + x;
      }
    }
  }

  if (debug)
    printf("Sum of all boxes GPS coordinates: ");
  return result;
}

struct PairComparerUp {
  bool
  operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const {
    return (a.first <= b.first) ? true : a.second <= b.second;
  }
};
struct PairComparerDown {
  bool
  operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const {
    return (a.first >= b.first) ? true : a.second >= b.second;
  }
};

int puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_15.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  std::pair<unsigned, unsigned> pos(0, 0);

  // get the map
  std::vector<std::vector<char>> map;
  std::vector<char> line = read_line<char>(file);
  while (line.size() > 0) {
    map.push_back({});
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == 'O') {
        map[map.size() - 1].push_back('[');
        map[map.size() - 1].push_back(']');
      } else if (line[i] == '@') {
        pos.first = map.size() - 1;
        pos.second = 2 * i;
        map[map.size() - 1].push_back(line[i]);
        map[map.size() - 1].push_back('.');
      } else {
        map[map.size() - 1].push_back(line[i]);
        map[map.size() - 1].push_back(line[i]);
      }
    }
    line = read_line<char>(file);
  }
  // get the movement
  std::vector<char> movement;
  line = read_line<char>(file);
  while (line.size() > 0) {
    for (auto move : line) {
      movement.push_back(move);
    }
    line = read_line<char>(file);
  }
  file.close();
  unsigned numberMove = 1;
  for (auto move : movement) {
    // for up and won
    std::set<std::pair<int, int>, PairComparerUp> moveUp;
    std::set<std::pair<int, int>, PairComparerDown> moveDown;
    std::set<int> toCheck;
    std::set<int> toAdd;
    std::set<int> toRemove;
    bool blocked = false;
    bool clear = true;

    int endPos = -1;
    switch (move) {
    case '<':
      for (int x = pos.second - 1; x >= 0; --x) {
        if (map[pos.first][x] == '#') {
          endPos = -1;
          break;
        } else if (map[pos.first][x] == '.') {
          endPos = x;
          break;
        }
      }
      if (endPos != -1) {
        for (int x = endPos; x < pos.second; ++x) {
          printf("{%d,%d}, ", pos.first, x);
          map[pos.first][x] = map[pos.first][x + 1];
        }
        map[pos.first][pos.second] = '.';
        --pos.second;
      }
      break;
    case '>':
      for (int x = pos.second + 1; x < map[pos.first].size(); ++x) {
        if (map[pos.first][x] == '#') {
          endPos = -1;
          break;
        } else if (map[pos.first][x] == '.') {
          endPos = x;
          break;
        }
      }
      if (endPos != -1) {
        for (int x = endPos; x > pos.second; --x) {
          map[pos.first][x] = map[pos.first][x - 1];
          printf("{%d,%d}, ", pos.first, x);
        }
        map[pos.first][pos.second] = '.';
        ++pos.second;
      }
      break;
    case '^':
      toCheck.insert(pos.second);
      for (int y = pos.first - 1; y >= 0; --y) {
        clear = true;
        for (int x : toCheck) {
          moveUp.insert({y + 1, x});
          if (map[y][x] == '#') {
            blocked = true;
            break;
          } else if (map[y][x] == '[') {
            clear = false;
            toAdd.insert(x + 1);
          } else if (map[y][x] == ']') {
            clear = false;
            toAdd.insert(x - 1);
          } else if (map[y][x] == '.') {
            toRemove.insert(x);
          }
        }

        // cannot move
        if (blocked)
          break;
        // move submarine
        if (clear) {
          for (auto [y, x] : moveUp) {
            printf("{%d,%d}, ", y, x);
            map[y - 1][x] = map[y][x];
            map[y][x] = '.';
          }
          --pos.first;
          break;
        }

        // add positions neede to check
        for (auto &&x : toAdd) {
          toCheck.insert(x);
        }
        // remove positions fromchecking
        for (auto &&x : toRemove) {
          toCheck.erase(x);
        }
        toAdd.clear();
        toRemove.clear();
      }
      break;
    case 'v':
      toCheck.insert(pos.second);
      for (int y = pos.first + 1; y < map.size(); ++y) {
        clear = true;
        for (auto x : toCheck) {
          moveDown.insert({y - 1, x});
          if (map[y][x] == '#') {
            blocked = true;
            break;
          } else if (map[y][x] == '[') {
            clear = false;
            toAdd.insert(x + 1);
          } else if (map[y][x] == ']') {
            clear = false;
            toAdd.insert(x - 1);
          } else if (map[y][x] == '.') {
            toRemove.insert(x);
          }
        }
        // cannot move
        if (blocked)
          break;
        // move submarine
        if (clear) {
          for (auto &&[y, x] : moveDown) {
            printf("{%d,%d}, ", y, x);
            map[y + 1][x] = map[y][x];
            map[y][x] = '.';
          }
          ++pos.first;
          break;
        }

        // add positions neede to check
        for (auto x : toAdd) {
          toCheck.insert(x);
        }

        // remove positions fromchecking
        for (auto x : toRemove) {
          toCheck.erase(x);
        }
        toAdd.clear();
        toRemove.clear();
      }
    }

    if (debug) {
      printf("%u-Move %c:\n", numberMove, move);
      for (auto &&line : map) {
        for (auto &&character : line) {
          printf("%c", character);
        }
        printf("\n");
      }
      printf("\n");
    }
    ++numberMove;
  }

  // calculate result for boxes
  int result = 0;
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].size(); ++x) {
      if (map[y][x] == '[') {
        result += 100 * y + x;
      }
    }
  }

  if (debug)
    printf("Sum of all boxes GPS coordinates: ");
  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 1412971
  std::cout << "Result Puzzle 2: " << puzzle_two(debug)
            << "\n"; // solution: 1429299
  return 0;
}