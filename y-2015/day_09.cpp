#include "../include/reader.h"
#include <cmath>
#include <iostream>
#include <map>
#include <set>

int puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_xx.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::vector<std::string>> lines = read_full_file<std::string>(file, ' ');
  file.close();

  std::map<std::string, std::set<std::pair<std::string, int>>> connections;
  std::vector<std::vector<std::string>> possibleRoutes;
  int result = 0;
  // Make map with locations and distances
  for (auto line : lines) {
    if (connections.find(line[0]) != connections.end())
      connections[line[0]].insert({line[2], std::stoi(line[4])});
    else
      connections.insert(
          std::pair<std::string, std::set<std::pair<std::string, int>>>(
              line[0], {{line[2], std::stoi(line[4])}}));

    if (connections.find(line[2]) != connections.end())
      connections[line[2]].insert({line[0], std::stoi(line[4])});
    else
      connections.insert(
          std::pair<std::string, std::set<std::pair<std::string, int>>>(
              line[2], {{line[0], std::stoi(line[4])}}));
  }

  // get all possible routes
  
  for (auto [city, destinations] : connections) {
    std::vector<std::string> route = {city};
  }

  return result;
}

int puzzle_two(bool debug) { return -1; }

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzle_one(debug) << "\n"; // solution:
  std::cout << "Result Puzzle 2: " << puzzle_two(debug) << "\n"; // solution:
  return 0;
}