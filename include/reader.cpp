#include "reader.h"

std::string &trim(std::string &input, char trimc) {
  while (input[0] == trimc)
    input.erase(input.begin());
  while (input[input.size() - 1] == trimc)
    input.pop_back();
  return input;
}

std::string &trim_one_side(std::string &input, char trimc, bool left) {
  while (left && input[0] == trimc)
    input.erase(input.begin());
  while (!left && input[input.size() - 1] == trimc)
    input.pop_back();
  return input;
}

std::vector<std::string> seperate(std::string input, char delimiter) {
  std::vector<std::string> result;
  std::string word;

  for (auto character : input) {
    if (character == delimiter) {
      result.push_back(word);
      word.clear();
      continue;
    }
    word.push_back(character);
  }
  result.push_back(word);

  return result;
}