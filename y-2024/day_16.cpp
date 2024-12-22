#include "../include/reader.h"
#include <cstring>
#include <iostream>

enum Direction { NORTH, EAST, SOUTH, WEST };

struct Field {
  unsigned x, y, cost;
  bool walkable, onShortestPath;
};

unsigned puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_16.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  Field start;
  Field end;

  std::vector<std::vector<Field>> map;
  std::vector<char> line = read_line<char>(file);
  unsigned y = 0;
  while (!line.empty()) {
    map.push_back({});
    for (int x = 0; x < line.size(); x++) {
      Field field;
      field.x = x;
      field.y = y;
      field.cost = -1;
      field.walkable = line[x] != '#';
      if (line[x] == 'S') {
        start.x = x;
        start.y = y;
        start.cost = 0;
        field.cost = 0;
      } else if (line[x] == 'E') {
        end.x = x;
        end.y = y;
        end.cost = -1;
      }
      map[y].push_back(field);
    }
    line = read_line<char>(file);
    ++y;
  }
  file.close();
  if (debug) {
    printf("\n");
    for (auto &&line : map) {
      for (auto &&field : line) {
        if (field.x == start.x && field.y == start.y)
          printf("S");
        else if (field.x == end.x && field.y == end.y)
          printf("E");
        else if (field.walkable)
          printf(".");
        else
          printf("#");
      }
      printf("\n");
    }
  }

  // Fields with bool if a turn is needed
  std::vector<std::pair<Field, Direction>> stack = {{start, EAST}};
  bool starting = true;
  while (!stack.empty()) {
    Field current = stack.back().first;
    Direction direction = stack.back().second;
    stack.pop_back();

    if (starting) {
      starting = false;
      // Chek west
      if (map[current.y][current.x - 1].walkable) {
        map[current.y][current.x - 1].cost = 2 * 1000 + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
    }

    switch (direction) {
    case EAST:
      // chekc north
      if (map[current.y - 1][current.x].walkable &&
          map[current.y - 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y - 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y - 1][current.x], NORTH});
      }
      // check east
      if (map[current.y][current.x + 1].walkable &&
          map[current.y][current.x + 1].cost >= current.cost + 1) {
        map[current.y][current.x + 1].cost = current.cost + 1;
        stack.push_back({map[current.y][current.x + 1], EAST});
      }
      // check south
      if (map[current.y + 1][current.x].walkable &&
          map[current.y + 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y + 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y + 1][current.x], SOUTH});
      }
      break;
    case SOUTH:
      // check east
      if (map[current.y][current.x + 1].walkable &&
          map[current.y][current.x + 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x + 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x + 1], EAST});
      }
      // check south
      if (map[current.y + 1][current.x].walkable &&
          map[current.y + 1][current.x].cost >= current.cost + 1) {
        map[current.y + 1][current.x].cost = current.cost + 1;
        stack.push_back({map[current.y + 1][current.x], SOUTH});
      }
      // check west
      if (map[current.y][current.x - 1].walkable &&
          map[current.y][current.x - 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x - 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
      break;
    case WEST:
      // chekc north
      if (map[current.y - 1][current.x].walkable &&
          map[current.y - 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y - 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y - 1][current.x], NORTH});
      }
      // check west
      if (map[current.y][current.x - 1].walkable &&
          map[current.y][current.x - 1].cost >= current.cost + 1) {
        map[current.y][current.x - 1].cost = current.cost + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
      // check south
      if (map[current.y + 1][current.x].walkable &&
          map[current.y + 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y + 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y + 1][current.x], SOUTH});
      }
      break;
    case NORTH:
      // check east
      if (map[current.y][current.x + 1].walkable &&
          map[current.y][current.x + 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x + 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x + 1], EAST});
      }
      // check north
      if (map[current.y - 1][current.x].walkable &&
          map[current.y - 1][current.x].cost >= current.cost + 1) {
        map[current.y - 1][current.x].cost = current.cost + 1;
        stack.push_back({map[current.y - 1][current.x], NORTH});
      }
      // check west
      if (map[current.y][current.x - 1].walkable &&
          map[current.y][current.x - 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x - 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
      break;
    }
  }

  if (debug)
    printf("\nShortest Route cost is: ");

  return map[end.y][end.x].cost;
}

unsigned puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_16.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }

  Field start;
  Field end;

  std::vector<std::vector<Field>> map;
  std::vector<char> line = read_line<char>(file);
  unsigned y = 0;
  while (!line.empty()) {
    map.push_back({});
    for (int x = 0; x < line.size(); x++) {
      Field field;
      field.x = x;
      field.y = y;
      field.cost = -1;
      field.walkable = line[x] != '#';
      if (line[x] == 'S') {
        start.x = x;
        start.y = y;
        start.cost = 0;
        field.cost = 0;
      } else if (line[x] == 'E') {
        end.x = x;
        end.y = y;
        end.cost = -1;
      }
      map[y].push_back(field);
    }
    line = read_line<char>(file);
    ++y;
  }
  file.close();
  if (debug) {
    printf("\n");
    for (auto &&line : map) {
      for (auto &&field : line) {
        if (field.x == start.x && field.y == start.y)
          printf("S");
        else if (field.x == end.x && field.y == end.y)
          printf("E");
        else if (field.walkable)
          printf(".");
        else
          printf("#");
      }
      printf("\n");
    }
  }

  // Fields with bool if a turn is needed
  std::vector<std::pair<Field, Direction>> stack = {{start, EAST}};
  bool starting = true;
  while (!stack.empty()) {
    Field current = stack.back().first;
    Direction direction = stack.back().second;
    stack.pop_back();

    if (starting) {
      starting = false;
      // Chek west
      if (map[current.y][current.x - 1].walkable) {
        map[current.y][current.x - 1].cost = 2 * 1000 + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
    }

    switch (direction) {
    case EAST:
      // chekc north
      if (map[current.y - 1][current.x].walkable &&
          map[current.y - 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y - 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y - 1][current.x], NORTH});
      }
      // check east
      if (map[current.y][current.x + 1].walkable &&
          map[current.y][current.x + 1].cost >= current.cost + 1) {
        map[current.y][current.x + 1].cost = current.cost + 1;
        stack.push_back({map[current.y][current.x + 1], EAST});
      }
      // check south
      if (map[current.y + 1][current.x].walkable &&
          map[current.y + 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y + 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y + 1][current.x], SOUTH});
      }
      break;
    case SOUTH:
      // check east
      if (map[current.y][current.x + 1].walkable &&
          map[current.y][current.x + 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x + 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x + 1], EAST});
      }
      // check south
      if (map[current.y + 1][current.x].walkable &&
          map[current.y + 1][current.x].cost >= current.cost + 1) {
        map[current.y + 1][current.x].cost = current.cost + 1;
        stack.push_back({map[current.y + 1][current.x], SOUTH});
      }
      // check west
      if (map[current.y][current.x - 1].walkable &&
          map[current.y][current.x - 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x - 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
      break;
    case WEST:
      // chekc north
      if (map[current.y - 1][current.x].walkable &&
          map[current.y - 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y - 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y - 1][current.x], NORTH});
      }
      // check west
      if (map[current.y][current.x - 1].walkable &&
          map[current.y][current.x - 1].cost >= current.cost + 1) {
        map[current.y][current.x - 1].cost = current.cost + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
      // check south
      if (map[current.y + 1][current.x].walkable &&
          map[current.y + 1][current.x].cost >= current.cost + 1000 + 1) {
        map[current.y + 1][current.x].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y + 1][current.x], SOUTH});
      }
      break;
    case NORTH:
      // check east
      if (map[current.y][current.x + 1].walkable &&
          map[current.y][current.x + 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x + 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x + 1], EAST});
      }
      // check north
      if (map[current.y - 1][current.x].walkable &&
          map[current.y - 1][current.x].cost >= current.cost + 1) {
        map[current.y - 1][current.x].cost = current.cost + 1;
        stack.push_back({map[current.y - 1][current.x], NORTH});
      }
      // check west
      if (map[current.y][current.x - 1].walkable &&
          map[current.y][current.x - 1].cost >= current.cost + 1000 + 1) {
        map[current.y][current.x - 1].cost = current.cost + 1000 + 1;
        stack.push_back({map[current.y][current.x - 1], WEST});
      }
      break;
    }
  }

  // find paths
  unsigned maxCost = map[end.y][end.x].cost;
  starting = true;
  stack.push_back({map[end.y][end.x], EAST});
  Field current;
  Field last;
  while (!stack.empty()) {
    if (!starting) {
      last = current;
    }
    current = stack.back().first;
    Direction direction = stack.back().second;
    stack.pop_back();

    // Chek west
    if (map[current.y][current.x - 1].walkable &&
        (map[current.y][current.x - 1].cost == current.cost - 1 ||
         map[current.y][current.x - 1].cost == current.cost - 1001 ||
         (map[current.y][current.x - 1].cost == current.cost + 999 &&
          direction == WEST))) {
      map[current.y][current.x - 1].onShortestPath = true;
      stack.push_back({map[current.y][current.x - 1], WEST});
    }
    // chekc north
    if (map[current.y - 1][current.x].walkable &&
        (map[current.y - 1][current.x].cost == current.cost - 1 ||
         map[current.y - 1][current.x].cost == current.cost - 1001 ||
         (map[current.y - 1][current.x].cost == current.cost + 999 &&
          direction == NORTH))) {
      map[current.y - 1][current.x].onShortestPath = true;
      stack.push_back({map[current.y - 1][current.x], NORTH});
    }
    // check east
    if (map[current.y][current.x + 1].walkable &&
        (map[current.y][current.x + 1].cost == current.cost - 1 ||
         map[current.y][current.x + 1].cost == current.cost - 1001 ||
         (map[current.y][current.x + 1].cost == current.cost + 999 &&
          direction == EAST))) {
      map[current.y][current.x + 1].onShortestPath = true;
      stack.push_back({map[current.y][current.x + 1], EAST});
    }
    // check south
    if (map[current.y + 1][current.x].walkable &&
        (map[current.y + 1][current.x].cost == current.cost - 1 ||
         map[current.y + 1][current.x].cost == current.cost - 1001 ||
         (map[current.y + 1][current.x].cost == current.cost + 999 &&
          direction == SOUTH))) {
      map[current.y + 1][current.x].onShortestPath = true;
      stack.push_back({map[current.y + 1][current.x], SOUTH});
    }
    starting = false;
  }

  unsigned spots = 0;
  if (debug)
    printf("\n");
  for (auto &&line : map) {
    for (auto &&field : line) {
      if (field.x == start.x && field.y == start.y) {
        ++spots;
        if (debug)
          printf("S");
      } else if (field.x == end.x && field.y == end.y) {
        ++spots;
        if (debug)
          printf("E");
      } else if (field.onShortestPath) {
        ++spots;
        if (debug)
          printf("O");
      } else if (field.walkable) {
        if (debug)
          printf(".");
      } else {
        if (debug)
          printf("#");
      }
    }
    if (debug)
      printf("\n");
  }
  if (debug)
    printf("\nPossible locations: ");

  return spots;
}

int main(int argc, char *argv[]) {
  if (argc != 3)
    return -1;

  bool debug = !strcmp(argv[2], "1");

  if (!strcmp(argv[1], "0") || !strcmp(argv[1], "1"))
    std::cout << "Result Puzzle 1: " << puzzle_one(debug)
              << "\n"; // solution: 99460
  if (!strcmp(argv[1], "0") || !strcmp(argv[1], "2"))
    std::cout << "Result Puzzle 2: " << puzzle_two(debug)
              << "\n"; // solution: 500
  return 0;
}