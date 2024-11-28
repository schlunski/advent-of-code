#pragma once

#include <fstream>
#include <string>
#include <vector>

/**
 * read a Line from the file
 *
 * @param[in] file file to read a line from
 * @param[in] delimiter seperator for the lines, by default no delimiter
 *
 * @return words in line seperated by delimiter
 */
std::vector<std::string> readLine(std::fstream &file, char delimiter = '\0');

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
std::vector<std::vector<std::string>> readFullFile(
    std::fstream &file, char delimiter = '\0', int skipLines = 0,
    bool columnwise = false);

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
 * Seperate a Sring by delimiter without changing the string
 *
 * @param[in] input string to configure
 * @param[in] delimiter seperator for the string
 *
 * @return words seperated by delimiter
 */
std::vector<std::string> seperate(std::string input, char delimiter);