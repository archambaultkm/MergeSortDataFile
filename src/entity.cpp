//
// Created by Kaitlyn Archambault on 2023-11-27.
//

#include "../inc/utils.h"
#include "../inc/entity.h"

#include <map>
#include <variant>
#include <sstream>

// Initialize the static sort field
int Entity::m_sort_field = 0;

bool Entity::empty() {
    return m_attributes.empty();
}

void Entity::set_sort_field(int field) {
    m_sort_field = field;
}

void Entity::set_attribute(int key, const std::string& value) {
    m_attributes[key] = value;
}

std::variant<std::string, int, float> Entity::get_attribute(int key) const {
    auto iter = m_attributes.find(key);

    if (iter != m_attributes.end()) {
        if (is_int(iter->second)) return stoi(iter->second);
        if (is_float(iter->second)) return stof(iter->second);

        return iter->second;
    }

    // key was not found
    throw std::out_of_range("Key not found");
}

bool Entity::operator<(const Entity& other) const {
    return compare_attributes(other, std::less());
}

bool Entity::operator<=(const Entity& other) const {
    return compare_attributes(other, std::less_equal());
}

bool Entity::operator>(const Entity& other) const {
    return compare_attributes(other, std::greater());
}

bool Entity::operator>=(const Entity& other) const {
    return compare_attributes(other, std::greater_equal());
}

bool Entity::operator==(const Entity& other) const {
    return compare_attributes(other, std::equal_to());
}

bool Entity::operator!=(const Entity& other) const {
    return compare_attributes(other, std::not_equal_to());
}

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    for (const auto& pair : entity.m_attributes) {
        os << pair.second << '\t';
    }

    return os;
}

std::istream& getline(std::istream& is, Entity& entity) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        int key = Entity::M_INDEX_BASE;
        std::string value;

        while (std::getline(iss, value, '\t')) {
            // Increment key for each value
            entity.set_attribute(key, value);
            key++;
        }
    }

    if (entity.empty() || is.eof()) {
        is.setstate(std::ios::failbit);  // Set the fail bit if we tried to read at the end of the stream
    }

    return is;
}
