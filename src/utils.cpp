/**
 * @file utils.cpp
 * @brief Implementations of helper functions
 * @author Kaitlyn Archambault
 * @date 2023-10-31
 */
#include "../inc/utils.h"

#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>

std::string remove_non_alpha(const std::string& str) {
    std::string corrected;

    // iterate through each character and only keep it if it's in the alphabet
    for (char c : str) {
        if (std::isalpha(c)) {
            corrected += c;
        }
    }

    return corrected;
}

std::vector<std::string> get_vec_from_file(const std::string& file_path) {
    // read the file at the provided file path into vector
    std::ifstream ifs;
    std::string line;
    std::vector<std::string> words;

    // attempt to open the provided file and read its contents into the list
    try {
        ifs.open(file_path, std::fstream::in);

        while (getline(ifs, line)) {
            // Split the line into words based on spaces
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
        }

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading file to dynamic array" << std::endl;
    }

    return words;
}

bool is_valid_file_path(const std::string &provided_file_path, std::string extension) {
    // create a string for a file path using the desired extension
    std::string extension_regex = extension.empty() ? "" : ("\\." + extension);
    std::string path_regex = R"(^(?:..)?\/?(?:[a-zA-Z0-9_-]+[\/])?(?:[a-zA-Z0-9_-]+)" + extension_regex + "$)";

    // create regex from the string
    std::regex valid_file_path(path_regex);

    // compare the provided file path and the correct regex
    return std::regex_match(provided_file_path, valid_file_path);
}

// made from pseudocode found at https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
int levenshtein_distance(const std::string& a, const std::string& b) {
    int m = a.length();
    int n = b.length();

    // Create a 2D vector to store the distances
    std::vector<std::vector<int>> d(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int substitution_cost = (a[i - 1] == b[j - 1]) ? 0 : 1;

            d[i][j] = std::min({d[i - 1][j] + 1,                        // deletion
                                d[i][j - 1] + 1,                        // insertion
                                d[i - 1][j - 1] + substitution_cost});  // substitution

            if (i > 1 && j > 1 && a[i] == b[j-1] && a[i-1] == b[j]) {
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + 1);       // transposition
            }
        }
    }

    // d[m][n] now contains the smallest number of changes needed to transform one word into the other
    return d[m][n];
}