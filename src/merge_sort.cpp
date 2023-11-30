//
// Created by Kaitlyn Archambault on 2023-11-28.
//

#include "../inc/merge_sort.h"

#include <string>
#include <fstream>

namespace sort {
    // Function to create a temporary file and return its filename
    std::string create_temp_file() {
        char filename[] = "tempfileXXXXXX";
        int fd = mkstemp(filename);
        //close(fd); // Close the file descriptor to keep the file open
        return filename;
    }
}