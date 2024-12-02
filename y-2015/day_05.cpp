#include "../include/reader.h"
#include <algorithm>
#include <iostream>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_05.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file);

  std::string vowels = "aeiou";
  std::vector<std::string> badWord = {"ab", "cd", "pq", "xy"};

  int result = 0;

  for (auto &&line : lines) {
    int countVovewls = 0;
    bool pair = false;
    bool naughty = false;
    std::string last;
    for (auto &&character : line[0]) {
      if (vowels.find(character) != std::string::npos)
        ++countVovewls;
      last.push_back(character);

      if (last.size() < 2) {
        continue;
      }

      // check for pair
      if (last[0] == last[1]) {
        pair = true;
      }
      // check for naughty
      if (std::find(badWord.begin(), badWord.end(), last) != badWord.end()) {
        naughty = true;
        break;
      }
      last.erase(last.begin());
    }

    if (!naughty && countVovewls > 2 && pair) {
      ++result;
    }
  }

  file.close();

  return result;
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_05.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file);

  std::string vowels = "aeiou";

  int result = 0;
  int lineNumb = 1;
  for (auto &&line : lines) {
    bool hasPair = false;
    bool hasRepeat = false;
    std::vector<std::string> pairs{};
    std::string last;
    std::string lastWord;

    std::string wordWithPair;
    std::string reapetingLetters;
    for (auto &&character : line[0]) {
      last.push_back(character);

      if (last.size() > 1) {
        std::string word{last[last.size() - 2]};
        word.push_back(character);
        if (std::find(pairs.begin(), pairs.end(), word) != pairs.end() &&
            std::find(pairs.begin(), pairs.end(), word) != pairs.end() - 1) {
          hasPair = true;
          wordWithPair = word;
        } else {
          pairs.push_back(word);
        }
      }

      if (last.size() == 3) {
        // check repeat
        if (last[0] == last[2]) {
          hasRepeat = true;
          reapetingLetters = last;
        }
        last.erase(last.begin());
      }
    }

    if (hasRepeat && hasPair) {
      ++result;
      if (debug)
        std::cout << lineNumb << ": " << reapetingLetters << ", "
                  << wordWithPair << "\n";
    }
    ++lineNumb;
  }

  file.close();

  return result;
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug) << "\n"; // solution: 236
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution: 51
  return 0;
}