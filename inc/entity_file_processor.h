//
// Created by Kaitlyn Archambault on 2023-11-27.
//

#ifndef ASSIGNMENT4_ENTITY_FILE_PROCESSOR_H
#define ASSIGNMENT4_ENTITY_FILE_PROCESSOR_H

#include <queue>
#include <string>

#include "entity.h"

class EntityFileProcessor {
private:
    std::queue<Entity<int, std::string>> m_queue; // store every entity found in the file to memory

public:
    EntityFileProcessor() = default;
    EntityFileProcessor(const std::string& file_name);
    void read_from_file(const std::string& file_name, const char& delimiter);
    void write_to_file(const std::string& file_name);
    void sort_by_field(int field);
    void print_queue(); // TODO replace with ostream operator
};


#endif //ASSIGNMENT4_ENTITY_FILE_PROCESSOR_H
