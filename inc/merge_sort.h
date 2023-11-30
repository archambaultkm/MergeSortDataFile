//
// Created by Kaitlyn Archambault on 2023-11-28.
//

#ifndef ASSIGNMENT4_MERGE_SORT_H
#define ASSIGNMENT4_MERGE_SORT_H

#include <string>
#include <fstream>
#include <vector>

namespace sort {
    // Create a temporary file and return its filename
    std::string create_temp_file();

    // Sort a temporary file
    template <typename DataT>
    void sort_temp_file(const std::string& temp_filename) {
        std::ifstream temp_file(temp_filename);
        std::vector<DataT> values;
        DataT current_data;

        while (getline(temp_file, current_data)) {
            values.push_back(current_data);
        }

        temp_file.close();

        std::sort(values.begin(), values.end());

        std::ofstream sorted_temp_file(temp_filename);
        for (const auto& value : values) {
            sorted_temp_file << value << '\n';
        }

        sorted_temp_file.close();
    }

    // Split input into small chunks, sort each chunk, and write to temporary files
    template <typename DataT>
    void split_and_sort_batch(const std::string& in_file, const std::string& temp_filename1, const std::string& temp_filename2) {
        std::ofstream temp_file1(temp_filename1);
        std::ofstream temp_file2(temp_filename2);

        DataT current_data;
        std::ifstream in(in_file);

        while (getline(in, current_data)) {
            temp_file1 << current_data << '\n';

            if (getline(in, current_data)) {
                temp_file2 << current_data << '\n';

            } else {

                break;
            }
        }

        temp_file1.close();
        temp_file2.close();

        // Sort the temporary files
        sort_temp_file<DataT>(temp_filename1);
        sort_temp_file<DataT>(temp_filename2);
    }

    template <typename DataT>
    void merge_sorted_batch(const std::string& out_file, const std::string& temp_filename1, const std::string& temp_filename2) {
        // Open input files for reading
        std::ifstream file1(temp_filename1);
        std::ifstream file2(temp_filename2);

        // Open output file for writing
        std::ofstream out(out_file);

        // Variables to store the current values from each file
        DataT value1, value2;

        // Read the first value from each file
        if (!getline(file1 >> std::ws, value1)|| !getline(file2 >> std::ws, value2)) {
            // One of the files is empty, nothing to merge
            return;
        }

        while (true) {
            // Compare values from both files and write the smaller one to the output file
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

        // Close the files
        file1.close();
        file2.close();
        out.close();
    }

    // Perform merge sort using temporary files
    template <typename DataT>
    void merge_sort(std::string file) {
        // Create temporary files for sorting
        std::string temp_filename1 = create_temp_file();
        std::string temp_filename2 = create_temp_file();

        // Split input into small chunks, sort each chunk, and write to temporary files
        split_and_sort_batch<DataT>(file, temp_filename1, temp_filename2);

        // Merge sorted chunks using temporary files
        merge_sorted_batch<DataT>(file, temp_filename1, temp_filename2);

        // Clean up temporary files
        std::remove(temp_filename1.c_str());
        std::remove(temp_filename2.c_str());
    }
}

#endif //ASSIGNMENT4_MERGE_SORT_H
