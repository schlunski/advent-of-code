#include "../include/reader.h"
#include <cstring>
#include <iostream>
#include <math.h>

std::string run_programm(
    unsigned long long a, unsigned long long b, unsigned long long c, std::vector<int> programm, bool debug) {
  bool jump = false;
  std::string result;
  for (int pc = 0; pc < programm.size(); pc += 2) {
    if (jump)
      pc -= 2;
    jump = false;

    if (debug)
      printf("%d: ", pc);

    std::string out;
    switch (programm[pc]) {
    case 0:
      // adv
      if (debug)
        printf("adv %llu / ", a);

      if (programm[pc + 1] < 4) {
        a /= int(pow(2, programm[pc + 1]));

        if (debug)
          printf("%d => ", int(pow(2, programm[pc + 1])));
      } else if (programm[pc + 1] == 4) {
        if (debug)
          printf("%d => ", int(pow(2, a)));

        a /= int(pow(2, a));
      } else if (programm[pc + 1] == 5) {
        a /= int(pow(2, b));

        if (debug)
          printf("%d => ", int(pow(2, b)));
      } else if (programm[pc + 1] == 6) {
        a /= int(pow(2, c));

        if (debug)
          printf("%d => ", int(pow(2, c)));
      }
      break;
    case 1:
      // bxl
      if (debug)
        printf("bxl %llu | %d => ", b, programm[pc + 1]);

      b ^= programm[pc + 1];
      break;
    case 2:
      // bst
      if (debug)
        printf("bst ");

      if (programm[pc + 1] < 4) {
        b = programm[pc + 1];

        if (debug)
          printf("%d => ", programm[pc + 1]);
      } else if (programm[pc + 1] == 4) {
        b = a & 7;

        if (debug)
          printf("%llu => ", a & 7);
      } else if (programm[pc + 1] == 5) {
        if (debug)
          printf("%llu => ", b & 7);

        b = b & 7;
      } else if (programm[pc + 1] == 6) {
        b = c & 7;

        if (debug)
          printf("%llu => ", c & 7);
      }
      break;
    case 3:
      // jnz
      if (a == 0)
        break;
      if (debug)
        printf("jnz %d => ", programm[pc + 1]);

      pc = programm[pc + 1];
      jump = true;
      break;
    case 4:
      // bxc
      if (debug)
        printf("bxc %llu ^ %llu => ", b, c);

      b ^= c;
      break;
    case 5:
      // out
      if (debug)
        printf("out ");

      if (programm[pc + 1] < 4) {
        out = std::to_string(programm[pc + 1]);
      } else if (programm[pc + 1] == 4) {
        out = std::to_string(a & 7);
      } else if (programm[pc + 1] == 5) {
        out = std::to_string(b & 7);
      } else if (programm[pc + 1] == 6) {
        out = std::to_string(c & 7);
      }

      for (auto c : out) {
        result = result + c + ",";

        if (debug)
          printf("%c", c);
      }
      if (debug)
        printf(" => ");
      break;
    case 6:
      // bdv
      if (debug)
        printf("bdv %llu / ", a);

      if (programm[pc + 1] < 4) {
        b = a / int(pow(2, programm[pc + 1]));
        if (debug)
          printf("%d => ", int(pow(2, programm[pc + 1])));
      } else if (programm[pc + 1] == 4) {
        b = a / int(pow(2, a));
        if (debug)
          printf("%d => ", int(pow(2, a)));
      } else if (programm[pc + 1] == 5) {
        b = a / int(pow(2, b));
        if (debug)
          printf("%d => ", int(pow(2, b)));
      } else if (programm[pc + 1] == 6) {
        b = a / int(pow(2, c));
        if (debug)
          printf("%d => ", int(pow(2, c)));
      }
      break;
    case 7:
      // cdv
      if (debug)
        printf("cdv %llu / ", a);

      if (programm[pc + 1] < 4) {
        c = a / int(pow(2, programm[pc + 1]));
        if (debug)
          printf("%d => ", int(pow(2, programm[pc + 1])));
      } else if (programm[pc + 1] == 4) {
        c = a / int(pow(2, a));
        if (debug)
          printf("%d => ", int(pow(2, a)));
      } else if (programm[pc + 1] == 5) {
        c = a / int(pow(2, b));
        if (debug)
          printf("%d => ", int(pow(2, b)));
      } else if (programm[pc + 1] == 6) {
        c = a / int(pow(2, c));
        if (debug)
          printf("%d => ", int(pow(2, c)));
      }
      break;
    }

    if (debug) {
      printf("{A:%llu, B:%llu, C:%llu}\n", a, b, c);
    }
  }
  result.pop_back();
  return result;
}

std::string puzzle_one(bool debug) {
  std::fstream file("puzzle_inputs/input_17.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  // get the registers
  unsigned a = std::stoi(read_line<std::string>(file, ' ')[2]);
  unsigned b = std::stoi(read_line<std::string>(file, ' ')[2]);
  unsigned c = std::stoi(read_line<std::string>(file, ' ')[2]);
  read_line<std::string>(file);
  std::vector<std::string> line = read_line<std::string>(file, ',');
  std::vector<int> programm = {std::stoi(std::string{line[0].back()})};
  for (int i = 1; i < line.size(); i++) {
    programm.push_back(std::stoi(line[i]));
  }

  return run_programm(a, b, c, programm, debug);
}

unsigned long long puzzle_two(bool debug) {
  std::fstream file("puzzle_inputs/input_17.txt");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file!\n";
    return 0;
  }
  unsigned long long a = 59900000000000;
  // unsigned long long a = 50000241562493;
  read_line<std::string>(file);
  unsigned b = std::stoi(read_line<std::string>(file, ' ')[2]);
  unsigned c = std::stoi(read_line<std::string>(file, ' ')[2]);
  read_line<std::string>(file);
  std::vector<std::string> line = read_line<std::string>(file, ',');
  std::vector<int> programm = {std::stoi(std::string{line[0].back()})};
  std::string programmAsString;
  programmAsString.push_back(line[0].back());
  programmAsString.push_back(',');
  for (int i = 1; i < line.size(); i++) {
    programm.push_back(std::stoi(line[i]));
    programmAsString += line[i] + ",";
  }
  programmAsString.pop_back();
  file.close();

  std::string result = run_programm(a, b, c, programm, false);
  if (debug)
    printf("Testing %llu\t%s\n", a, result.c_str());

  while (programmAsString != result) {
    ++a;
    result = run_programm(a, b, c, programm, false);
    if (debug)
      printf("Testing %llu\t%s\n", a, result.c_str());
  }

  if (debug)
    printf("Value of A: ");
  return a;
}

int main(int argc, char *argv[]) {
  if (argc != 3)
    return -1;

  bool debug = !strcmp(argv[2], "1");

  if (!strcmp(argv[1], "0") || !strcmp(argv[1], "1"))
    std::cout << "Result Puzzle 1: " << puzzle_one(debug)
              << "\n"; // solution: 2,7,6,5,6,0,2,3,1
  if (!strcmp(argv[1], "0") || !strcmp(argv[1], "2"))
    std::cout << "Result Puzzle 2: " << puzzle_two(debug) << "\n"; // solution:
  return 0;
}