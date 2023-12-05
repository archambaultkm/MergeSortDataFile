//
// Created by Kaitlyn Archambault on 2023-11-27.
//

#ifndef ASSIGNMENT4_ENTITY_H
#define ASSIGNMENT4_ENTITY_H

#include "../inc/utils.h"

#include <map>
#include <variant>
#include <sstream>

template <typename DataT>
class Entity {
private:
    std::map<int, DataT> m_attributes; // this entity's attributes
    static int m_sort_field; // the field to sort on, same for all entities
    static constexpr int M_INDEX_BASE = 1; // determines what number "key" index starts on

public:
    Entity() = default;

    void clear() {
        m_attributes.clear();
    }

    // Setter for the sort field
    static void set_sort_field(int field) {
        m_sort_field = field;
    }

    void set_attribute(int key, const DataT& value) {
        m_attributes[key] = value;
    }

    // TODO make this apply to template instances where DataT is string, make generic one just return second
    std::variant<DataT, int, float> get_attribute(int key) const {
        auto iter = m_attributes.find(key);

        if (iter != m_attributes.end()) {
            if (is_int(iter->second)) {
                return stoi(iter->second);

            } else if (is_float(iter->second)) {
                return stof(iter->second);
            }

            return iter->second;

        } else { // TODO this is strange
            // key was not found
            throw std::out_of_range("Key not found");
        }
    }

    template <typename Operator>
    bool compare_attributes(const Entity& other, Operator op) const {
        try {
            return op(get_attribute(m_sort_field), other.get_attribute(m_sort_field));

        } catch (const std::out_of_range&) {
            // Consider uninitialized entities, or those without data at that key, less than
            return true;
        }
    }

    // Comparison operator (<) based on m_sort_field
    bool operator<(const Entity& other) const {
        return compare_attributes(other, std::less());
    }

    // Comparison operator (<=) based on m_sort_field
    bool operator<=(const Entity& other) const {
        return compare_attributes(other, std::less_equal());
    }

    // Comparison operator (>) based on m_sort_field
    bool operator>(const Entity& other) const {
        return compare_attributes(other, std::greater());
    }

    // Comparison operator (>=) based on m_sort_field
    bool operator>=(const Entity& other) const {
        return compare_attributes(other, std::greater_equal());
    }

    // Equality operator (==) based on m_sort_field
    bool operator==(const Entity& other) const {
        return compare_attributes(other, std::equal_to());
    }

    // Inequality operator (!=) based on m_sort_field
    bool operator!=(const Entity& other) const {
        return compare_attributes(other, std::not_equal_to());
    }

    // Overload << operator to print all attributes
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity) {
        for (const auto& pair : entity.m_attributes) {
            os << pair.second << '\t';
        }

        return os;
    }

    // Overload the extraction operator
    friend std::istream& operator>>(std::istream& is, const Entity& entity) {
        int key = entity.m_attributes.size();
        DataT value;

        while (getline(is, entity, '\t')) {
            // Increment key for each value
            entity.set_attribute(key, value);
            key++;
        }

        return is;
    }

    // Overload std::getline to extract data from a stream into an Entity
    friend std::istream& getline(std::istream& is, Entity& entity) {
        std::string line;
        if (std::getline(is, line)) {
            std::istringstream iss(line);
            int key = M_INDEX_BASE;
            DataT value;

            while (std::getline(iss, value, '\t')) {
                // Increment key for each value
                entity.set_attribute(key, value);
                key++;
            }
        }

        return is;
    }
};

// Initialize the static sort field
template <typename DataT>
int Entity<DataT>::m_sort_field = 0;


#endif //ASSIGNMENT4_ENTITY_H
