#pragma once

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

/**
 * read a Line from the file
 *
 * @param[in] file file to read a line from
 * @param[in] delimiter seperator for the lines, by default no delimiter
 *
 * @return words in line seperated by delimiter
 */
template <typename T>
std::vector<T> read_line(std::fstream &file, char delimiter = '\0') {
  std::vector<T> result = {};

  std::string word("");
  char tmp;

  while (file.get(tmp)) {
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
      if constexpr (std::is_same<T, std::string>::value) {
        result.push_back(word);
      } else if constexpr (std::is_same<T, int>::value) {
        result.push_back(std::stoi(word));
      } else if constexpr (std::is_same<T, long>::value) {
        result.push_back(std::stol(word));
      } else if constexpr (std::is_same<T, unsigned long>::value) {
        result.push_back(std::stoul(word));
      } else if constexpr (std::is_same<T, unsigned long long>::value) {
        result.push_back(std::stoull(word));
      } else if constexpr (std::is_same<T, char>::value) {
        result.push_back(tmp);
      } else {
        throw std::invalid_argument("Not compatible Type");
      }
      word.clear();
    } else {
      if constexpr (std::is_same<T, char>::value) {
        result.push_back(tmp);
        continue;
      }
      word.push_back(tmp); // extend word
    }
  }

  if constexpr (std::is_same<T, std::string>::value) {
    result.push_back(word);
  } else if constexpr (std::is_same<T, int>::value) {
    result.push_back(std::stoi(word));
  } else if constexpr (std::is_same<T, long>::value) {
    result.push_back(std::stol(word));
  } else if constexpr (std::is_same<T, unsigned long>::value) {
    result.push_back(std::stoul(word));
  } else if constexpr (std::is_same<T, unsigned long long>::value) {
    result.push_back(std::stoull(word));
  } else if constexpr (!std::is_same<T, char>::value)  {
    throw std::invalid_argument("Not compatible Type");
  }

  return result;
}

/**
 * read the full file:
 *
 * @param[in] file file to read a line from
 * @param[in] delimiter seperator for the lines, by default no delimiter
 * @param[in] skipLines deticates how many line in the file should be skipped
 * @param[in] collumwise deticates if sorted collum- or rowwise
 *
 * @return Table of word in the file
 */
template <class T>
std::vector<std::vector<T>> read_full_file(
    std::fstream &file, char delimiter = '\0', int skipLines = 0,
    bool columnwise = false) {
  std::vector<std::vector<T>> result({{}});

  // Skip lines
  for (int i = 0; i < skipLines; i++) {
    read_line<T>(file);
  }

  bool first = true;
  while (!file.eof()) {
    std::vector<T> line = read_line<T>(file, delimiter);

    if (columnwise) {
      for (size_t column = 0; column < line.size(); column++) {
        if (first && column < line.size() - 1)
          result.push_back(std::vector<T>{});
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

/**
 * Trim all trailing characters
 *
 * @param[in] input string to configure
 * @param[in] trimc character the gets ereased from input
 *
 * @return trimmed string
 */
std::string &trim(std::string &input, char trimc);
/**
 * Trim all trailing characters on one side
 *
 * @param[in] input string to configure
 * @param[in] trimc character the gets ereased from input
 * @param[in] left indicates wich side to trim
 *
 * @return trimmed string
 */
std::string &trim_one_side(std::string &input, char trimc, bool left);
/**
 * Seperate a Sring by delimiter without changing the string
 *
 * @param[in] input string to configure
 * @param[in] delimiter seperator for the string
 *
 * @return words seperated by delimiter
 */
std::vector<std::string> seperate(std::string input, char delimiter);