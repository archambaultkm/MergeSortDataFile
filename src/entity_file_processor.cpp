//
// Created by Kaitlyn Archambault on 2023-11-27.
//

#include <fstream>
#include <sstream>
#include <iostream>

#include "../inc/entity_file_processor.h"

void EntityFileProcessor::read_from_file(const std::string &file_name, const char& delimiter) {
    std::ifstream ifs;
    std::string line;

    // attempt to open the provided file and read its contents into the queue
    try {
        ifs.open(file_name, std::fstream::in);

        // Each line in the document represents an entity
        while (getline(ifs, line)) {
            Entity<int, std::string> entity;

            // Read each value into attributes
            std::istringstream iss(line);
            std::string word;
            int key = 1;
            while (std::getline(iss, word, delimiter)) {
                entity.set_attribute(key, word);
                key++;
            }

            m_queue.push(entity);
        }

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading file" << std::endl;
    }
}

void EntityFileProcessor::print_queue() {
    // print out all the entities that got loaded to the queue
    while (!m_queue.empty()) {
        std::cout << m_queue.front() << std::endl;
        m_queue.pop();
    }
}
