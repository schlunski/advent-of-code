#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_07.txt");
  std::vector<std::vector<std::string>> lines = readFullFile(file, ' ');

  std::map<std::string, uint16_t> wires;
  // wire, line, signal
  std::vector<std::tuple<std::string, int, uint16_t>> wiresAddedInInteration;

  int countIterations = 0;

  while (wires.size() < lines.size()) {
    if (debug)
      std::cout << "\tNext iteration:\n";
    int lineNumber = 0;
    wiresAddedInInteration.clear();
    for (auto line : lines) {
      ++lineNumber;
      // Already a signal on wire
      if (wires.find(line[line.size() - 1]) != wires.end())
        continue;

      switch (line.size()) {
      // Wire/Signal to wire
      case 3:
        try {
          int signal = std::stoi(line[0]);
          wires.insert({line[2], signal});
          wiresAddedInInteration.push_back({line[2], lineNumber, signal});
        } catch (const std::exception &e) {
          if (wires.find(line[0]) == wires.end())
            break;
          wires.insert({line[2], wires[line[0]]});
          wiresAddedInInteration.push_back(
              {line[2], lineNumber, wires[line[0]]});
        }
        break;
      case 4:
        try {
          int signal = std::stoi(line[1]);
          wires.insert({line[3], signal});
          wiresAddedInInteration.push_back({line[3], lineNumber, ~signal});
          if (debug)
            std::cout << "\nNOT signal to wire\n";
        } catch (const std::exception &e) {
          if (wires.find(line[1]) == wires.end())
            break;

          wires.insert({line[3], wires[line[1]]});
          wiresAddedInInteration.push_back(
              {line[3], lineNumber, ~wires[line[1]]});
        }
        break;
      case 5:
        bool signalOnRight = false;
        bool signalOnLeft = false;
        uint16_t signalLeft = 0;
        uint16_t signalRight = 0;

        try {
          signalLeft = std::stoi(line[0]);
          signalOnLeft = true;
        } catch (const std::exception &e) {
        }
        try {
          signalRight = std::stoi(line[2]);
          signalOnRight = true;
        } catch (const std::exception &e) {
        }
        uint16_t signalOnWIre = 0;
        bool isSignalOnWire = false;
        // -------------------------------------------------------------
        if (line[1] == "AND") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft & signalRight;
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] & wires[line[2]];
            isSignalOnWire = true;
          } else if (
              signalOnLeft &&
              wires.find(line[2]) != wires.end()) { // left number
            signalOnWIre = signalLeft & wires[line[2]];
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] & signalRight;
            isSignalOnWire = true;
          }
          // -------------------------------------------------------------
        } else if (line[1] == "OR") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft | signalRight;
            isSignalOnWire = true;
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft | wires[line[2]];
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] | signalRight;
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] | wires[line[2]];
            isSignalOnWire = true;
          }
          // -------------------------------------------------------------
        } else if (line[1] == "RSHIFT") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft >> signalRight;
            isSignalOnWire = true;
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft >> wires[line[2]];
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] >> signalRight;
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] >> wires[line[2]];
            isSignalOnWire = true;
          }
          // -------------------------------------------------------------
        } else if (line[1] == "LSHIFT") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft << signalRight;
            isSignalOnWire = true;
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft << wires[line[2]];
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] << signalRight;
            isSignalOnWire = true;
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] << wires[line[2]];
            isSignalOnWire = true;
          }
        }
        if (isSignalOnWire) {
          wires.insert({line[4], signalOnWIre});
          wiresAddedInInteration.push_back({line[4], lineNumber, signalOnWIre});
        }
      }
    }

    if (debug) {
      for (auto &&[wire, line, signal] : wiresAddedInInteration) {
        std::cout << "Line " << line << ": " << wire << "=" << signal << "\n";
      }
    }

    ++countIterations;
  }

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