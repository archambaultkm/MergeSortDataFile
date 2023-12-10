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

// Function to create a temporary file and return its filename
std::string create_temp_file() {
    char filename[] = "tempfileXXXXXX";
    int fd = mkstemp(filename);
    //close(fd); // Close the file descriptor to keep the file open
    return filename;
}

int parse_int_from_char(const char* input) {
    int result = 0;
    const char* ptr = input;

    // Skip non-numeric characters and the '=' sign
    while (*ptr && !isdigit(*ptr)) {
        ++ptr;
    }

    // Parse the numeric part
    while (*ptr && isdigit(*ptr)) {
        result = result * 10 + (*ptr - '0');
        ++ptr;
    }

    return result;
}

bool regex_match(const char* input, const std::string& regex_pattern) {
    std::regex pattern(regex_pattern);
    std::cmatch match;

    return std::regex_search(input, match, pattern);
}

bool is_int(char* char_p) {
    try {
        size_t pos;
        std::stoi(char_p, &pos);
        if (pos != std::strlen(char_p)) {

            return false;
        }

    } catch (const std::invalid_argument& e) {

        return false;  // The string couldn't be converted to a float, return the string
    } catch (const std::out_of_range& e) {

        return false;  // The converted value is out of the range representable by float, return the string
    }

    return true;
}

bool is_int(const std::string& string) {
    try {
        size_t pos;
        std::stoi(string, &pos);
        if (pos != string.length()) {

            return false;
        }

    } catch (const std::invalid_argument& e) {

        return false;  // The string couldn't be converted to an int, return the string
    } catch (const std::out_of_range& e) {

        return false;  // The converted value is out of the range representable by int, return the string
    }

    return true;
}

bool is_float(const std::string& string) {
    try {
        size_t pos;
        std::stof(string, &pos);
        if (pos != string.length()) {

            return false;
        }

    } catch (const std::invalid_argument& e) {

        return false;  // The string couldn't be converted to an int, return the string
    } catch (const std::out_of_range& e) {

        return false;  // The converted value is out of the range representable by int, return the string
    }

    return true;
}

bool is_positive_int(char* char_p) {
    if (!is_int(char_p)) return false;

    return std::stoi(char_p) > 0;
}

std::variant<float, std::string> convert_to_variant(const std::string& value) {
    try {
        size_t pos; // position of first char that couldn't be converted to an integer
        float floatValue = std::stof(value, &pos);

        // see if the whole value could be converted to a float
        if (pos == value.length()) {

            return floatValue;
        } else {

            return value;
        }

    } catch (const std::invalid_argument& e) {

        return value;  // The string couldn't be converted to a float, return the string
    } catch (const std::out_of_range& e) {

        return value;  // The converted value is out of the range representable by float, return the string
    }
}

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