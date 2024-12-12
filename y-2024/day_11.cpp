#include "../include/reader.h"
#include <iostream>

unsigned long long puzzle_one(bool debug, std::vector<std::string>& line, unsigned iterations=25, unsigned start = 1) {
  if (debug) {
    std::cout << "Initial arrangment:\n";
    for (auto numb : line) {
      std::cout << numb << " ";
    }
    std::cout << "\n";
  }

  for (size_t iteration = start; iteration < iterations+start; iteration++) {
    if (line.size() >= line.capacity() / 2) {
      line.reserve(line.capacity() * 2);
    }
    if (line.size() == line.max_size())
      throw;
    if (debug)
      std::cout << "On Iteration/blink: " << iteration << "\n";
    for (size_t i = 0; i < line.size(); ++i) {
      bool added = false;
      if (line[i] == "0") {
        line[i] = "1";
      } else if (line[i].size() % 2 == 0) {
        line.insert(
            line.begin() + i + 1,
            line[i].substr(line[i].size() / 2, line[i].size() / 2));
        line[i] = line[i].substr(0, line[i].size() / 2);
        added = true;
        ++i;
        trim_one_side(line[i], '0', true);
        if (line[i].empty())
          line[i] = "0";
      } else {
        line[i] = std::to_string(std::stoul(line[i]) * 2024);
      }
    }
    if (debug)
      std::cout << "\n";
  }

  if (debug)
    std::cout << "Number of stones after " << iterations << "Iterations: ";

  return line.size();
}

int puzzle_two(bool debug, std::vector<std::string>& line) { return puzzle_one(debug, line, 50, 25); }

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::fstream file("puzzle_inputs/input_11.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  std::vector<std::string> line = read_line(file, ' ');
  file.close();

  std::cout << "Result Puzzle 1: " << puzzle_one(debug, line) << "\n"; // solution: 186424
  std::cout << "Result Puzzle 2: " << puzzle_two(debug, line) << "\n"; // solution:
  return 0;
}