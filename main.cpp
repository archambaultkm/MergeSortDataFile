#include <iostream>

#include "inc/colours.h"
#include "inc/utils.h"
#include "inc/entity_file_processor.h"

using namespace std;

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

    EntityFileProcessor efp;
    efp.read_from_file(argv[1], '\t');
    efp.print_queue();

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

    // TODO check that argv[2] is a valid field#

    return true;
}