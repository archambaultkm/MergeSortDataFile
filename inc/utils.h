/**
 * @file utils.h
 * @brief Contains various helper functions not specific to this assignment.
 * @author Kaitlyn Archambault
 * @date 2023-10-31
 */

#ifndef ASSIGNMENT_3_UTILS_H
#define ASSIGNMENT_3_UTILS_H

#include <string>

// Create a temporary file and return its filename
std::string create_temp_file();

bool is_int(char* char_p);

bool is_int(const std::string& string);

bool is_float(const std::string& string);

bool is_positive_int(char* char_p);

std::variant<float, std::string> convert_to_variant(const std::string& value);

/**
 * Remove numbers or special characters from a provided string
 *
 * @param str the string to operate on
 *
 * @returns corrected string with no special characters
 */
std::string remove_non_alpha(const std::string& str);

/**
 * Get a vector of all words found in a text file
 *
 * @param file_path file path in .txt format
 *
 * @returns vector<string> of each word in the file
 */
std::vector<std::string> get_vec_from_file(const std::string& file_path);

/**
 * Validate provided file path with regex
 *
 * @param provided_file_path file path input by user
 * @param extension desired file extension
 *
 * @returns true if the provided file path is in a valid format, false otherwise
 * @note in the future it would be nice to be able to provide multiple extensions
 */
bool is_valid_file_path(const std::string &provided_file_path, std::string extension);

/**
 * @brief Calculate the Levenshtein distance between two strings.
 *
 * The Levenshtein distance is a measure of the similarity between two strings
 * by calculating the minimum number of single-character edits (insertions, deletions, substitutions, or transpositions)
 * required to change one string into the other.
 *
 * @param a The first input string.
 * @param b The second input string.
 * @return The Levenshtein distance between strings 'a' and 'b'.
 */
int levenshtein_distance(const std::string& a, const std::string& b);

/**
 * @brief Calculate the absolute difference between two values.
 *
 * @tparam T The type of values to compare.
 * @param a value 1.
 * @param b value 2.
 * @return The absolute difference between 'a' and 'b'.
 */
template <typename T>
T difference(T a, T b) {
    return (a > b) ? (a - b) : (b - a);
}

/**
 * @brief Calculate the difference between 2 strings in terms of the edit operations required
 * to transform one string into the other.
 *
 * @param a string 1.
 * @param b string 2.
 * @return The difference (Levenshtein distance) between strings 'a' and 'b'.
 */
inline int difference(const std::string& a, const std::string& b) {
    return levenshtein_distance(a, b);
}

#endif //ASSIGNMENT_3_UTILS_H
