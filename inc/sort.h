//
// Created by Kaitlyn Archambault on 2023-11-28.
//

#ifndef ASSIGNMENT4_SORT_H
#define ASSIGNMENT4_SORT_H

#include <string>

namespace ext_sort {
    // Split input in half and write to temporary files
    bool split_file(const std::string& in_file, const std::string& temp_filename1, const std::string& temp_filename2);

    // Merge two temp files back into the file they were split from
    void merge_files(const std::string& out_file, const std::string& temp_filename1, const std::string& temp_filename2);

    // Perform merge sort on a file using temporary files
    void merge_sort_file(const std::string& file);

    // Perform merge sort on a file using temporary files and set sort field
    void merge_sort_file(const std::string& file, int field_to_sort);
}

#endif //ASSIGNMENT4_SORT_H
