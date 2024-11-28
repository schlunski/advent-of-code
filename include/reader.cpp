#include "reader.h"

std::vector<std::string> readLine(std::fstream *file, char delimiter) {
  std::vector<std::string> result = {};

  std::string word("");
  char tmp;

  while (file->get(tmp)) {
    // line end
    if (tmp == '\n') {
      break;
    }
    // Carriage return
    if (tmp == char(13)) {
      continue;
    }
    // Word end
    if (tmp == delimiter) {
      result.push_back(word);
      word.clear();
    } else {
      word.push_back(tmp); // extend word
    }
  }
  result.push_back(word);

  return result;
}

std::vector<std::vector<std::string>> readFullFile(
    std::fstream *file, char delimiter, int skipLines, bool collumwise) {
  std::vector<std::vector<std::string>> result = {{}};

  // Skip lines
  for (int i = 0; i < skipLines; i++) {
    readLine(file);
  }

  bool first = true;
  while (!file->eof()) {
    std::vector<std::string> line = readLine(file, delimiter);

    if (collumwise) {
      for (size_t collum = 0; collum < line.size(); collum++) {
        if (first)
          result.push_back({});
        result[collum].push_back(line[collum]);
      }
      first = false;
    } else {
      result.push_back(line);
    }
  }

  return result;
}