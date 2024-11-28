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
    std::fstream *file, char delimiter, int skipLines, bool columnwise) {
  std::vector<std::vector<std::string>> result({{}});

  // Skip lines
  for (int i = 0; i < skipLines; i++) {
    readLine(file);
  }

  bool first = true;
  while (!file->eof()) {
    std::vector<std::string> line = readLine(file, delimiter);

    if (columnwise) {
      for (size_t column = 0; column < line.size(); column++) {
        if (first && column < line.size() - 1)
          result.push_back(std::vector<std::string>{});
        result[column].push_back(line[column]);
      }
      first = false;
    } else {
      if (first)
        result.pop_back();
      first = false;
      result.push_back(line);
    }
  }

  return result;
}