//
// Created by Kaitlyn Archambault on 2023-11-28.
//

#include "../inc/sort.h"

#include <string>
#include <fstream>

namespace ext_sort {
    // Split input in half and write to temporary files
    bool split_file(const std::string &in_file, const std::string &temp_filename1, const std::string &temp_filename2) {
        std::ofstream temp_file1(temp_filename1);
        std::ofstream temp_file2(temp_filename2);

        Entity current_data;
        std::ifstream in(in_file);
        int data_count = 0;

        while (getline(in, current_data)) {
            temp_file1 << current_data << '\n';
            data_count++;

            if (getline(in, current_data)) {
                temp_file2 << current_data << '\n';
                data_count++;
            }
        }

        temp_file1.close();
        temp_file2.close();

        return data_count > 2;
    }

    // Merge two temp files back into the file they were split from
    void merge_files(const std::string &out_file, const std::string &temp_filename1, const std::string &temp_filename2) {
        // Open input files for reading
        std::ifstream file1(temp_filename1);
        std::ifstream file2(temp_filename2);

        // Open output file for writing
        std::ofstream out(out_file);

        // Variables to store the current values from each file
        Entity value1, value2;

        // Read the first value from each file
        if (!getline(file1, value1)) {
            // possible only file 2 has data
            while (getline(file2, value2)) {
                out << value2 << '\n';
            }

        } else if (!getline(file2, value2)) {
            // possible only file 1 has data
            out << value1 << '\n';
            while (getline(file1, value1)) {
                out << value1 << '\n';
            }

        } else {
            while (true) {
                // Compare values from both files and write the smaller one to the output file first
                if (value1 <= value2) {
                    out << value1 << '\n';

                    // Try to read the next value from file1
                    if (!getline(file1, value1)) {
                        // file1 is exhausted, write the remaining values from file2
                        out << value2 << '\n';
                        while (getline(file2, value2)) {
                            out << value2 << '\n';
                        }
                        break;
                    }
                } else {
                    out << value2 << '\n';

                    // Try to read the next value from file2
                    if (!getline(file2, value2)) {
                        // file2 is exhausted, write the remaining values from file1
                        out << value1 << '\n';
                        while (getline(file1, value1)) {
                            out << value1 << '\n';
                        }
                        break;
                    }
                }
            }
        }

        // Close the files
        file1.close();
        file2.close();
        out.close();
    }

    // Perform merge sort on a file using temporary files
    void merge_sort_file(const std::string& file) {
        // Create temporary files for sorting
        std::string temp_filename1 = create_temp_file();
        std::string temp_filename2 = create_temp_file();

        try {
            // Split input into two batches and write to temporary files
            if (split_file(file, temp_filename1, temp_filename2)) {
                // if the file needs to be split further, recursively merge sort the two halves of the file
                merge_sort_file(temp_filename1);
                merge_sort_file(temp_filename2);
            }

            // Merge batches using temporary files
            merge_files(file, temp_filename1, temp_filename2);

        } catch (std::exception &e) {
            // Make sure files are removed if program throws an exception
            std::remove(temp_filename1.c_str());
            std::remove(temp_filename2.c_str());

            std::cout << e.what() << std::endl;
        }

        // Clean up temporary files
        std::remove(temp_filename1.c_str());
        std::remove(temp_filename2.c_str());
    }
}