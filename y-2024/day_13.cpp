#include "../include/reader.h"
#include <iostream>
#include <tuple>

unsigned puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_13.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ' ');
  file.close();

  // List of claw games with: {A:{X,Y}, B:{X,Y}, Prize:{X,Y}}
  std::vector<std::tuple<
      std::pair<unsigned long, unsigned long>,
      std::pair<unsigned long, unsigned long>,
      std::pair<unsigned long, unsigned long>>>
      clawGames;
  for (int i = 0; i < lines.size(); i += 4) {
    clawGames.push_back(
        // Button A: X
        {{std::stoul(seperate(trim(lines[i][2], ','), '+')[1]),
          // Button A: Y
          std::stoul(seperate(lines[i][3], '+')[1])},
         // Button B: X
         {std::stoul(seperate(trim(lines[i + 1][2], ','), '+')[1]),
          // Button B: Y
          std::stoul(seperate(lines[i + 1][3], '+')[1])},
         // Price: X
         {std::stoul(seperate(trim(lines[i + 2][1], ','), '=')[1]),
          // Price: Y
          std::stoul(seperate(lines[i + 2][2], '=')[1])}});
  }

  unsigned long result = 0;
  unsigned long clawGame = 1;
  for (auto &&[a, b, price] : clawGames) {
    // results
    unsigned long minTokens = -1;
    unsigned long minPressesA = 0;
    unsigned long minPressesB = 0;

    // strating position
    unsigned pressesB = 0;
    unsigned pressesA = price.first / a.first;
    if (pressesA > unsigned(price.second / a.second)) {
      pressesA = price.second / a.second;
    }
    long x = price.first - pressesA * a.first;
    long y = price.second - pressesA * a.second;

    unsigned iterations = pressesA;

    for (int i = 0; i < iterations; i++) {
      pressesB = x / b.first;
      // breaking conditions
      if (pressesB > 100 || pressesA == -1 || x < 0 || y < 0) {
        break;
      }

      // A more than 100 presses
      if (pressesA > 100) {
        --pressesA;
        x += a.first;
        y += a.second;
        continue;
      }

      // possible win
      if (x % b.first == 0 && y % b.second == 0 &&
          x / b.first == y / b.second) {
        unsigned tokensUsed = pressesA * 3 + pressesB;
        if (tokensUsed < minTokens) {
          minTokens = tokensUsed;
          minPressesA = pressesA;
          minPressesB = pressesB;
        }
      }

      --pressesA;
      x += a.first;
      y += a.second;
    }

    if (minTokens != -1) {
      result += minTokens;

      if (debug)
        printf(
            "Game %lu: A-%lu, B-%lu, T-%lu\n", clawGame, minPressesA,
            minPressesB, minTokens);
    }
    ++clawGame;
  }

  if (debug)
    printf("Overall tokens needed: ");
  return result;
}

unsigned puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_13.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ' ');
  file.close();

  // List of claw games with: {A:{X,Y}, B:{X,Y}, Prize:{X,Y}}
  std::vector<std::tuple<
      std::pair<unsigned long long, unsigned long long>,
      std::pair<unsigned long long, unsigned long long>,
      std::pair<unsigned long long, unsigned long long>>>
      clawGames;
  for (int i = 0; i < lines.size(); i += 4) {
    clawGames.push_back(
        // Button A: X
        {{std::stoull(seperate(trim(lines[i][2], ','), '+')[1]),
          // Button A: Y
          std::stoull(seperate(lines[i][3], '+')[1])},
         // Button B: X
         {std::stoull(seperate(trim(lines[i + 1][2], ','), '+')[1]),
          // Button B: Y
          std::stoull(seperate(lines[i + 1][3], '+')[1])},
         // Price: X
         {std::stoull(seperate(trim(lines[i + 2][1], ','), '=')[1]) + (10000000000000),
          // Price: Y
          std::stoull(seperate(lines[i + 2][2], '=')[1]) + (10000000000000)}});
  }

  unsigned long long result = 0;
  unsigned long clawGame = 1;
  for (auto &&[a, b, price] : clawGames) {
    // results
    unsigned long long minTokens = -1;
    unsigned long long minPressesA = 0;
    unsigned long long minPressesB = 0;

    // strating position
    unsigned long long pressesB = 0;
    unsigned long long pressesA = price.first / a.first;
    if (pressesA > unsigned(price.second / a.second)) {
      pressesA = price.second / a.second;
    }
    long long x = price.first - pressesA * a.first;
    long long y = price.second - pressesA * a.second;

    unsigned long long iterations = pressesA;

    for (unsigned long long i = 0; i < iterations; i++) {
      pressesB = x / b.first;
      // breaking conditions
      if (pressesB > 100 || pressesA == -1 || x < 0 || y < 0) {
        break;
      }

      // A more than 100 presses
      if (pressesA > 100) {
        --pressesA;
        x += a.first;
        y += a.second;
        continue;
      }

      // possible win
      if (x % b.first == 0 && y % b.second == 0 &&
          x / b.first == y / b.second) {
        unsigned long long tokensUsed = pressesA * 3 + pressesB;
        if (tokensUsed < minTokens) {
          minTokens = tokensUsed;
          minPressesA = pressesA;
          minPressesB = pressesB;
        }
      }

      --pressesA;
      x += a.first;
      y += a.second;
    }

    if (minTokens != -1) {
      result += minTokens;

      if (debug)
        printf(
            "Game %lu: A-%llu, B-%llu, T-%llu\n", clawGame, minPressesA,
            minPressesB, minTokens);
    }
    ++clawGame;
  }

  if (debug)
    printf("Overall tokens needed: ");
  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug)
            << "\n"; // solution: 32067
  std::cout << "Result Puzzle 2: " << puzzle_two(debug) << "\n"; // solution:
  return 0;
}