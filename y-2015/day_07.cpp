#include "../include/reader.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>

int puzzleOne(bool debug) {
  std::fstream file("puzzle_inputs/input_07.txt");
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ' ');

  std::map<std::string, uint16_t> wires;
  // wire, line, signal
  std::vector<std::tuple<std::string, int, uint16_t>> wiresAddedInInteration;

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

          if (debug)
            std::cout << signal << " signal to wire " << line[2] << "\n";
        } catch (const std::exception &e) {
          if (wires.find(line[0]) == wires.end())
            break;
          wires.insert({line[2], wires[line[0]]});
          wiresAddedInInteration.push_back(
              {line[2], lineNumber, wires[line[0]]});

          if (debug)
            std::cout << wires[line[0]] << " wire to wire " << line[2] << "\n";
        }
        break;
      case 4:
        try {
          int signal = std::stoi(line[1]);
          wires.insert({line[3], ~signal});
          wiresAddedInInteration.push_back({line[3], lineNumber, ~signal});
          if (debug)
            std::cout << "NOT " << signal << " signal to wire " << line[3]
                      << "\n";
        } catch (const std::exception &e) {
          if (wires.find(line[1]) == wires.end())
            break;

          wires.insert({line[3], ~wires[line[1]]});
          wiresAddedInInteration.push_back(
              {line[3], lineNumber, ~wires[line[1]]});

          if (debug)
            std::cout << "NOT " << wires[line[1]] << " signal to wire "
                      << line[3] << "\n";
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
            if (debug)
              std::cout << signalLeft << " signal AND signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft &&
              wires.find(line[2]) != wires.end()) { // left number
            signalOnWIre = signalLeft & wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal AND wire " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] & signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire AND signal " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] & wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]] << " wire AND wire "
                        << line[2] << ":" << wires[line[2]] << " to " << line[4]
                        << "\n";
          }
          // -------------------------------------------------------------
        } else if (line[1] == "OR") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft | signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal OR signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft | wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " wire OR signal " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] | signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire OR signal " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] | wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]] << " wire OR wire "
                        << line[2] << ":" << wires[line[2]] << " to " << line[4]
                        << "\n";
          }
          // -------------------------------------------------------------
        } else if (line[1] == "RSHIFT") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft >> signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal RSHIFT signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft >> wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal RSHIFT wire " << line[2]
                        << ":" << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] >> signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire RSHIFT signal " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] >> wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire RSHIFT wire " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          }
          // -------------------------------------------------------------
        } else if (line[1] == "LSHIFT") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft << signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal LSHIFT signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft << wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal LSHIFT wire " << line[2]
                        << ":" << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] << signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire LSHIFT wire " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] << wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire LSHIFT wire " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          }
        }
        if (isSignalOnWire) {
          wires.insert({line[4], signalOnWIre});
          wiresAddedInInteration.push_back({line[4], lineNumber, signalOnWIre});
        }
      }
    }

    if (debug) {
      std::cout << "\n";
      for (auto &&[wire, line, signal] : wiresAddedInInteration) {
        std::cout << "Line " << line << ": " << wire << "=" << signal << "\n";
      }
    }
  }

  file.close();

  if (debug)
    std::cout << "Result Puzzle 1: ";

  return wires["a"];
}

int puzzleTwo(bool debug) {
  std::fstream file("puzzle_inputs/input_07.txt");
  std::vector<std::vector<std::string>> lines =
      read_full_file<std::string>(file, ' ');

  std::map<std::string, uint16_t> wires;
  // wire, line, signal
  std::vector<std::tuple<std::string, int, uint16_t>> wiresAddedInInteration;

  wires.insert({"b", puzzleOne(false)});

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

          if (debug)
            std::cout << signal << " signal to wire " << line[2] << "\n";
        } catch (const std::exception &e) {
          if (wires.find(line[0]) == wires.end())
            break;
          wires.insert({line[2], wires[line[0]]});
          wiresAddedInInteration.push_back(
              {line[2], lineNumber, wires[line[0]]});

          if (debug)
            std::cout << wires[line[0]] << " wire to wire " << line[2] << "\n";
        }
        break;
      case 4:
        try {
          int signal = std::stoi(line[1]);
          wires.insert({line[3], ~signal});
          wiresAddedInInteration.push_back({line[3], lineNumber, ~signal});
          if (debug)
            std::cout << "NOT " << signal << " signal to wire " << line[3]
                      << "\n";
        } catch (const std::exception &e) {
          if (wires.find(line[1]) == wires.end())
            break;

          wires.insert({line[3], ~wires[line[1]]});
          wiresAddedInInteration.push_back(
              {line[3], lineNumber, ~wires[line[1]]});

          if (debug)
            std::cout << "NOT " << wires[line[1]] << " signal to wire "
                      << line[3] << "\n";
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
            if (debug)
              std::cout << signalLeft << " signal AND signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft &&
              wires.find(line[2]) != wires.end()) { // left number
            signalOnWIre = signalLeft & wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal AND wire " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] & signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire AND signal " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] & wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]] << " wire AND wire "
                        << line[2] << ":" << wires[line[2]] << " to " << line[4]
                        << "\n";
          }
          // -------------------------------------------------------------
        } else if (line[1] == "OR") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft | signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal OR signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft | wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " wire OR signal " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] | signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire OR signal " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] | wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]] << " wire OR wire "
                        << line[2] << ":" << wires[line[2]] << " to " << line[4]
                        << "\n";
          }
          // -------------------------------------------------------------
        } else if (line[1] == "RSHIFT") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft >> signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal RSHIFT signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft >> wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal RSHIFT wire " << line[2]
                        << ":" << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] >> signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire RSHIFT signal " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] >> wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire RSHIFT wire " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          }
          // -------------------------------------------------------------
        } else if (line[1] == "LSHIFT") {
          if (signalOnLeft && signalOnRight) { // both are numbers
            signalOnWIre = signalLeft << signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal LSHIFT signal " << signalRight
                        << " to " << line[4] << "\n";
          } else if (
              signalOnLeft && wires.find(line[2]) != wires.end()) { // left
                                                                    // number
            signalOnWIre = signalLeft << wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << signalLeft << " signal LSHIFT wire " << line[2]
                        << ":" << wires[line[2]] << " to " << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              signalOnRight) { // right number
            signalOnWIre = wires[line[0]] << signalRight;
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire LSHIFT wire " << signalRight << " to "
                        << line[4] << "\n";
          } else if (
              wires.find(line[0]) != wires.end() &&
              wires.find(line[2]) != wires.end()) { // no numbers
            signalOnWIre = wires[line[0]] << wires[line[2]];
            isSignalOnWire = true;

            if (debug)
              std::cout << line[0] << ":" << wires[line[0]]
                        << " wire LSHIFT wire " << line[2] << ":"
                        << wires[line[2]] << " to " << line[4] << "\n";
          }
        }
        if (isSignalOnWire) {
          wires.insert({line[4], signalOnWIre});
          wiresAddedInInteration.push_back({line[4], lineNumber, signalOnWIre});
        }
      }
    }

    if (debug) {
      std::cout << "\n";
      for (auto &&[wire, line, signal] : wiresAddedInInteration) {
        std::cout << "Line " << line << ": " << wire << "=" << signal << "\n";
      }
    }
  }

  file.close();

  if (debug)
    std::cout << "Result Puzzle 2: ";

  return wires["a"];
}

int main(int argc, char *argv[]) {
  bool debug = (argc > 1) ? true : false;
  std::cout << "Result Puzzle 1: a=" << puzzleOne(debug)
            << "\n\n"; // solution: 16076
  std::cout << "Result Puzzle 2: a=" << puzzleTwo(debug)
            << "\n"; // solution: 2797
  return 0;
}