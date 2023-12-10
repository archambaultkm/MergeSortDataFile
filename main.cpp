#include <iostream>

#include "inc/colours.h"
#include "inc/utils.h"
#include "inc/sort.h"
#include "inc/timer.h"

using std::string;
using std::cout;
using std::endl;

// expected program arguments, used as feedback to the user
const string EXPECTED_FORMAT = "\"./sort <filename>.txt -field=<field#>\"";
const int REQUIRED_NUM_ARGS = 3;

/**
 * Validate program arguments
 *
 * @return True if arguments provided are valid, false otherwise.
 * @note Prints feedback to the user with cout
 */
bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format);

int main(int argc, char* argv[]) {
    // Validate arguments (valid_arguments() provides feedback to the user if it fails)
    if (!valid_arguments(argc, REQUIRED_NUM_ARGS, argv, EXPECTED_FORMAT)) {

        return 1;
    }

    // initialize file and Entity sorting field from validated arguments
    string file_to_sort = argv[1];
    int sort_field = parse_int_from_char(argv[2]);

    // Print an indication that sorting has begun
    cout << "Starting sort..." << "\n";

    // Perform and time merge sort on the specified file
    Timer<> timer;
    timer.measure_function_time([&]() { ext_sort::merge_sort_file(file_to_sort, sort_field); });

    // Print the elapsed time for the sorting process
    cout << "Sort took " << timer.get_elapsed_time().value << " " << timer.get_elapsed_time().unit << endl;

    return 0;
}

bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format) {
    if (argc != expected_num_args) {
        cout << RED << "Wrong number of arguments: expected " << expected_num_args - 1 << " but " << argc - 1 << " were provided." << RESET << endl;
        cout << CYAN << "Correct usage: " << expected_format << RESET << endl;

        return false;
    }

    // sample file is expected to be a txt file
    std::string extension = "txt";
    if (!is_valid_file_path(argv[1], extension)) {
        cout << RED << "Must enter a valid " << "." << extension << " format file name for all provided files." << RESET << endl;
        cout << CYAN << "Correct usage: " << expected_format << RESET << endl;

        return false;
    }

    // second argument is expected in the format "-field=<#>"
    std::string arg2_format = R"(-field=\d{1,2})";
    if (!regex_match(argv[2], arg2_format)) {
        cout << RED << "Invalid argument: " << argv[2] << endl;
        cout << CYAN << "Correct usage: " << expected_format << RESET << endl;

        return false;
    }

    if (parse_int_from_char(argv[2]) <= 0) {
        cout << RED << "Invalid input: '" << argv[2] << "' must contain a positive integer to represent the field to sort on." << RESET << endl;

        return false;
    }

    return true;
}