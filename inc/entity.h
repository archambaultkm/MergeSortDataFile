//
// Created by Kaitlyn Archambault on 2023-11-27.
//

#ifndef ASSIGNMENT4_ENTITY_H
#define ASSIGNMENT4_ENTITY_H

#include "../inc/utils.h"

#include <map>
#include <variant>

class Entity {
private:
    std::map<int, std::string> m_attributes; // this entity's attributes
    static int m_sort_field; // the field to sort on, same for all entities
    static constexpr int M_INDEX_BASE = 1; // determines what number "key" index starts on

public:
    Entity() = default;

    // Setter for the sort field
    static void set_sort_field(int field);

    // set the attribute for a given key
    void set_attribute(int key, const std::string& value);

    // get the attribute at a given key, parsed to an accurate data type
    std::variant<std::string, int, float> get_attribute(int key) const;

    // compare two entities by their attribute at m_sort_field
    template <typename Operator>
    bool compare_attributes(const Entity& other, Operator op) const {
        try {
            return op(get_attribute(m_sort_field), other.get_attribute(m_sort_field));

        } catch (const std::out_of_range&) {
            // Consider uninitialized entities, or those without data at that key, something.
            // This should never be reached, just a safeguard.
            return true;
        }
    }

    // Comparison operator (<) based on m_sort_field
    bool operator<(const Entity& other) const;

    // Comparison operator (<=) based on m_sort_field
    bool operator<=(const Entity& other) const;

    // Comparison operator (>) based on m_sort_field
    bool operator>(const Entity& other) const;

    // Comparison operator (>=) based on m_sort_field
    bool operator>=(const Entity& other) const;

    // Equality operator (==) based on m_sort_field
    bool operator==(const Entity& other) const;

    // Inequality operator (!=) based on m_sort_field
    bool operator!=(const Entity& other) const;

    // Overload << operator to print all attributes
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity);

    // Overload std::getline to extract data from a stream into an Entity
    friend std::istream& getline(std::istream& is, Entity& entity);
};


#endif //ASSIGNMENT4_ENTITY_H
