#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_07.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, ' ');

  std::map<std::string, uint16_t> wires;
  std::cout << "Linesize: " << lines.size() << "\n";

  int countIterations = 0;
  std::vector<int> linesToDelete;
  do {
    linesToDelete.clear();
    if (debug)
      std::cout << "\tnext Iteration:\n";
    for (int lineNumb = 0; lineNumb < lines.size(); ++lineNumb) {  
      switch (lines[lineNumb].size()) {
      // signal to wire or wire to wire
      case 3:
        try {
          wires.insert(std::pair<std::string, uint16_t>(
              lines[lineNumb][lines[lineNumb].size() - 1],
              std::stoi(lines[lineNumb][0])));
          linesToDelete.push_back(lineNumb);
        } catch (const std::exception &e) {
          if (wires.find(lines[lineNumb][0]) == wires.end()) {
            break;
          }
          wires.insert(std::pair<std::string, uint16_t>(
              lines[lineNumb][lines[lineNumb].size() - 1],
              wires[lines[lineNumb][0]]));
          linesToDelete.push_back(lineNumb);
        }
        break;
      // NOT
      case 4:
        try {
          wires.insert(std::pair<std::string, uint16_t>(
              lines[lineNumb][lines[lineNumb].size() - 1],
              std::stoi(lines[lineNumb][1])));
          linesToDelete.push_back(lineNumb);
        } catch (const std::exception &e) {
          if (wires.find(lines[lineNumb][1]) == wires.end()) {
            break;
          }
          wires.insert(std::pair<std::string, uint16_t>(
              lines[lineNumb][lines[lineNumb].size() - 1],
              ~wires[lines[lineNumb][1]]));
          linesToDelete.push_back(lineNumb);
        }
        break;

      default:
        if (lines[lineNumb][1] == "AND" &&
            wires.find(lines[lineNumb][2]) != wires.end()) {
          try {
            wires.insert(std::pair<std::string, uint16_t>(
                lines[lineNumb][lines[lineNumb].size() - 1],
                std::stoi(lines[lineNumb][0]) & wires[lines[lineNumb][2]]));
            linesToDelete.push_back(lineNumb);
          } catch (const std::exception &e) {
            if (wires.find(lines[lineNumb][0]) == wires.end()) {
              break;
            }
            wires.insert(std::pair<std::string, uint16_t>(
                lines[lineNumb][lines[lineNumb].size() - 1],
                wires[lines[lineNumb][0]] & wires[lines[lineNumb][2]]));
            linesToDelete.push_back(lineNumb);
          }
        } else if (
            lines[lineNumb][1] == "OR" &&
            wires.find(lines[lineNumb][0]) != wires.end() &&
            wires.find(lines[lineNumb][2]) != wires.end()) {
          wires.insert(std::pair<std::string, uint16_t>(
              lines[lineNumb][lines[lineNumb].size() - 1],
              wires[lines[lineNumb][0]] | wires[lines[lineNumb][2]]));
          linesToDelete.push_back(lineNumb);
        } else if (
            lines[lineNumb][1] == "LSHIFT" &&
            wires.find(lines[lineNumb][0]) != wires.end()) {
          wires.insert(std::pair<std::string, uint16_t>(
              lines[lineNumb][lines[lineNumb].size() - 1],
              wires[lines[lineNumb][0]] << std::stoi(lines[lineNumb][2])));
          linesToDelete.push_back(lineNumb);
        } else if (
            lines[lineNumb][1] == "RSHIFT" &&
            wires.find(lines[lineNumb][0]) != wires.end()) {
          wires.insert(std::pair<std::string, uint16_t>(
              lines[lineNumb][lines[lineNumb].size() - 1],
              wires[lines[lineNumb][0]] >> std::stoi(lines[lineNumb][2])));
          linesToDelete.push_back(lineNumb);
        }
        break;
      }

      if (debug && linesToDelete.size() > 0 &&
          linesToDelete[linesToDelete.size() - 1] == lineNumb)
        std::cout << lineNumb + 1 << "-"
                  << lines[lineNumb][lines[lineNumb].size() - 1] << ": "
                  << wires[lines[lineNumb][lines[lineNumb].size() - 1]] << "\n";
      ++lineNumb;
    }

    std::sort(linesToDelete.begin(), linesToDelete.end());
    std::cout << "Delete Lines: ";
    for (int i = linesToDelete.size() - 1; i >= 0; --i) {
      std::cout << linesToDelete[i] << ":"
                << lines[linesToDelete[i]][lines[linesToDelete[i]].size() - 1]
                << ", ";
      lines.erase(lines.begin() + linesToDelete[i]);
    }
    std::cout << "Linesize: " << lines.size() << "\n";
    ++countIterations;
  } while (!lines.empty() && countIterations < 20);
  

  file.close();

  return wires["a"];
}

int puzzleTwo(bool debug) {}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: " << puzzleOne(debug) << "\n"; // solution:
  std::cout << "Result Puzzle 2: " << puzzleTwo(debug) << "\n"; // solution:
  return 0;
}