#include <iostream>

#include "inc/colours.h"
#include "inc/utils.h"
#include "inc/entity.h"
#include "inc/merge_sort.h"
#include "inc/timer.h"

using std::string;
using std::cout;
using std::endl;

// expected program arguments, used as feedback to the user
const string EXPECTED_FORMAT = "\"./merge <filename>.txt -<field#>\"";
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

    // Set the sort field in the Entity class
    int sort_field = std::stoi(argv[2]);
    Entity<string>::set_sort_field(sort_field);

    // Print an indication that sorting has begun
    cout << "Starting sort..." << "\n";
    string file_to_sort = argv[1];

    // Perform and time merge sort on the specified file
    Timer<> timer;
    sort::merge_sort_file(file_to_sort);
    timer.stop();

    // Print the elapsed time for the sorting process
    cout << "Sort took " << timer.get_elapsed_time_s() << " seconds. " << endl;

    return 0;
}

bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format) {
    if (argc != expected_num_args) {
        cout << RED << "Wrong number of arguments: expected " << expected_num_args - 1 << " but " << argc - 1 << " were provided." << RESET << endl;
        cout << CYAN << "Correct usage: " << expected_format << RESET << endl;

        return false;
    }

    // sample file is expected to be a txt file
    string extension = "txt";
    if (!is_valid_file_path(argv[1], extension)) {
        cout << RED << "Must enter a valid " << "." << extension << " format file name for all provided files." << RESET << endl;
        cout << CYAN << "Correct usage: " << expected_format << RESET << endl;

        return false;
    }

    if (!is_positive_int(argv[2])) {
        cout << "Invalid input: '" << argv[2] << "' must contain a positive integer to represent the field to sort on." << endl;

        return false;
    }

    return true;
}