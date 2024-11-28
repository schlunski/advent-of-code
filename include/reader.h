#pragma once

#include <fstream>
#include <string>
#include <vector>

/**
 * read a Line from the file
 *
 * @param[in] file file to read a line from
 * @param[in] delimiter by default no delimiter
 *
 * @return words in line seperated by delimiter
 */
std::vector<std::string> readLine(std::fstream *file, char delimiter = '\0');

/**
 * read the full file:
 *
 * @param[in] file file to read a line from
 * @param[in] delimiter seperator for the lines
 * @param[in] skipLines deticates how many line in the file should be skipped
 * @param[in] collumwise deticates if sorted collum- or rowwise
 *
 * @return Table of word in the file
 */
std::vector<std::vector<std::string>> readFullFile(
    std::fstream *file, char delimiter, int skipLines = 0,
    bool columnwise = true);