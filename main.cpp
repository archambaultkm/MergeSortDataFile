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

/**
 * Validate program arguments
 *
 * @return True if arguments provided are valid, false otherwise.
 * @note Prints feedback to the user with cout
 */
bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format);

int main(int argc, char* argv[]) {
    if (!valid_arguments(argc, 3, argv, EXPECTED_FORMAT)) {

        return 1;
    }

    string file_to_sort = argv[1];

    Timer<> timer;
    cout << "Starting sort..." << "\n";
    timer.start();

    sort::merge_sort<Entity<int, string>>(file_to_sort);
    //sort::merge_sort<string>(file_to_sort);

    timer.stop();

    cout << "Sort took " << timer.get_elapsed_time() << "ms. " << endl;

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

    if (!is_int(argv[2])) {
        cout << "Invalid input: '" << argv[2] << "' is not a valid integer." << endl;

        return false;
    }

    if (!is_positive(argv[2])) {
        cout << "Invalid input: '" << argv[2] << "' must be a positive integer to represent the field to sort on." << endl;

        return false;
    }

    return true;
}