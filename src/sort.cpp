//
// Created by Kaitlyn Archambault on 2023-11-28.
//

#include "../inc/sort.h"

#include <string>
#include <fstream>
#include <iostream>

#include "../inc/utils.h"
#include "../inc/entity.h"

namespace ext_sort {
    bool split_file(const std::string &in_file, const std::string &temp_filename1, const std::string &temp_filename2) {
        std::ofstream temp_file1(temp_filename1);
        std::ofstream temp_file2(temp_filename2);

        Entity current_data;
        std::ifstream in(in_file);
        int data_count = 0;

        //as long as the in file has data, split it equally between the two temp files
        while (getline(in, current_data)) {
            temp_file1 << current_data << '\n';
            data_count++;

            if (getline(in, current_data)) {
                temp_file2 << current_data << '\n';
                data_count++;
            }
        }

        // return if the file should continue to be split for merge sort purposes
        return data_count > 1;
    }

    void merge_files(const std::string &out_file, const std::string &temp_filename1, const std::string &temp_filename2) {
        // Open input/output files
        std::ifstream file1(temp_filename1);
        std::ifstream file2(temp_filename2);
        std::ofstream out(out_file);

        // Entities to store the current values from each file
        Entity value1, value2;

        // Read the first value from each file
        if (!getline(file1, value1)) {
            // file1 is empty, copy the remaining values from file2
            while (getline(file2, value2)) {
                out << value2 << '\n';
            }
            return;
        }

        if (!getline(file2, value2)) {
            // file2 is empty, copy the remaining values from file1
            out << value1 << '\n';
            while (getline(file1, value1)) {
                out << value1 << '\n';
            }
            return;
        }

        // loop until one of the files is exhausted
        while (!file1.eof() || !file2.eof()) {
            // Compare values from both files and write the smaller one to the output file first
            if (value1 <= value2) {
                out << value1 << '\n';

                // Try to read the next value from file1
                if (!getline(file1, value1)) {
                    // file1 is exhausted, write the remaining values from file2 and break
                    out << value2 << '\n';
                    while (getline(file2, value2)) {
                        out << value2 << '\n';
                    }
                }

            } else {
                out << value2 << '\n';

                // Try to read the next value from file2
                if (!getline(file2, value2)) {
                    // file2 is exhausted, write the remaining values from file1 and break
                    out << value1 << '\n';
                    while (getline(file1, value1)) {
                        out << value1 << '\n';
                    }
                }
            }
        }
    }

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

    void merge_sort_file(const std::string& file, int field_to_sort) {
        Entity::set_sort_field(field_to_sort);
        merge_sort_file(file);
    }
}