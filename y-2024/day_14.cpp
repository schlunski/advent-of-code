#include "../include/reader.h"
#include <chrono>
#include <iostream>
#include <thread>

struct Robot {
  int posX, posY;
  int velX, velY;
};

int puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_14.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ' ');
  file.close();

  std::vector<Robot> robots;
  for (auto &&line : lines) {
    Robot bot;
    std::string pos = seperate(line[0], '=')[1];
    bot.posX = std::stoi(seperate(pos, ',')[0]);
    bot.posY = std::stoi(seperate(pos, ',')[1]);
    std::string vel = seperate(line[1], '=')[1];
    bot.velX = std::stoi(seperate(vel, ',')[0]);
    bot.velY = std::stoi(seperate(vel, ',')[1]);
    robots.push_back(bot);
  }

  int width = 101;
  int heigth = 103;
  int seconds = 100;

  // For debug
  std::vector<std::vector<int>> debugMap(heigth, std::vector<int>(width));

  unsigned quad1 = 0;
  unsigned quad2 = 0;
  unsigned quad3 = 0;
  unsigned quad4 = 0;

  for (auto bot : robots) {
    for (int i = 0; i < seconds; i++) {
      bot.posX = (bot.posX + bot.velX) % width;
      if (bot.posX < 0)
        bot.posX += width;
      bot.posY = (bot.posY + bot.velY) % heigth;
      if (bot.posY < 0)
        bot.posY += heigth;
    }
    ++debugMap[bot.posY][bot.posX];
    // Quadrant 1
    if (bot.posX < width / 2 && bot.posY < heigth / 2) {
      ++quad1;
    }
    // Quadrant 2
    else if (bot.posX > width / 2 && bot.posY < heigth / 2) {
      ++quad2;
    }
    // Quadrant 3
    else if (bot.posX > width / 2 && bot.posY > heigth / 2) {
      ++quad3;
    }
    // Quadrant 4
    else if (bot.posX < width / 2 && bot.posY > heigth / 2) {
      ++quad4;
    }
  }

  if (debug) {
    printf("Map at the end:\n");
    for (int i = 0; i < heigth; i++) {
      for (int j = 0; j < width; j++) {
        if (i != heigth / 2 && j != width / 2)
          if (debugMap[i][j] != 0)
            printf("%d", debugMap[i][j]);
          else
            printf(".");
        else
          printf(" ");
      }
      printf("\n");
    }
    printf(
        "Quad 1: %u, Quad 2: %u, Quad 3: %u, Quad 4: %u\n", quad1, quad2, quad3,
        quad4);
    printf("Safety factor is: ");
  }

  return quad1 * quad2 * quad3 * quad4;
}

int puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_14.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ' ');
  file.close();

  std::vector<Robot> robots;
  for (auto &&line : lines) {
    Robot bot;
    std::string pos = seperate(line[0], '=')[1];
    bot.posX = std::stoi(seperate(pos, ',')[0]);
    bot.posY = std::stoi(seperate(pos, ',')[1]);
    std::string vel = seperate(line[1], '=')[1];
    bot.velX = std::stoi(seperate(vel, ',')[0]);
    bot.velY = std::stoi(seperate(vel, ',')[1]);
    robots.push_back(bot);
  }

  int width = 101;
  int heigth = 103;
  unsigned seconds = 100;

  for (unsigned iteration = 0; iteration < unsigned(-1); iteration++) {
    // For debug
    std::vector<std::vector<int>> map(heigth, std::vector<int>(width));
    bool different = true;
    for (auto &&bot : robots) {
      bot.posX = (bot.posX + bot.velX) % width;
      if (bot.posX < 0)
        bot.posX += width;
      bot.posY = (bot.posY + bot.velY) % heigth;
      if (bot.posY < 0)
        bot.posY += heigth;
      ++map[bot.posY][bot.posX];
      if (map[bot.posY][bot.posX] > 1)
        different = false;
    }
    if (different) {
      if (debug) {
        printf("Map at iteration %d:\n", iteration + 1);
        for (int i = 0; i < heigth; i++) {
          for (int j = 0; j < width; j++) {
            if (map[i][j] != 0)
              printf("%d", map[i][j]);
            else
              printf(".");
          }
          printf("\n");
        }
        printf("Christmas Tree after ");
      }
      for (auto &&line : map) {
        unsigned counter = 0;
        for (auto &&number : line) {
          if (counter == 0 && number == 0) {
            continue;
          } else if (number == 0) {
            break;
          }
          ++counter;
        }
        if (counter > 30) {
          return iteration;
        }
      }
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 219150360
  std::cout << "Result Puzzle 2: " << puzzle_two(debug) << (debug ? " seconds" : " ")
            << "\n"; // solution: 8053
  return 0;
}