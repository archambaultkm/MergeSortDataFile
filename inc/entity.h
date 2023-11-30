//
// Created by Kaitlyn Archambault on 2023-11-27.
//

#ifndef ASSIGNMENT4_ENTITY_H
#define ASSIGNMENT4_ENTITY_H

#include <map>
#include <sstream>

template <typename KeyT, typename DataT>
class Entity {
private:
    std::map<KeyT, DataT> m_attributes;
    int m_sort_field = 2;

public:
    Entity() = default;

    explicit Entity(int field) : m_sort_field(field) {};

    void clear() {
        m_attributes.clear();
    }

    void set_attribute(KeyT key, const DataT& value) {
        m_attributes[key] = value;
    }

    DataT get_attribute(int key) const {
        auto iter = m_attributes.find(key);

        if (iter != m_attributes.end()) {

            return iter->second;
        } else {
            // key was not found
            throw std::out_of_range("Key not found");
        }
    }

    // Comparison operator (<) based on m_sort_field
    bool operator<(const Entity& other) const {
        try {
            return get_attribute(m_sort_field) < other.get_attribute(m_sort_field);
        } catch (const std::out_of_range&) {
            // Consider uninitialized entities, or those without data at that key, less than
            return true;
        }
    }

    // Comparison operator (<=) based on m_sort_field
    bool operator<=(const Entity& other) const {
        return get_attribute(m_sort_field) <= other.get_attribute(m_sort_field);
    }

    // Comparison operator (>) based on m_sort_field
    bool operator>(const Entity& other) const {
        return get_attribute(m_sort_field) > other.get_attribute(m_sort_field);
    }

    // Comparison operator (>=) based on m_sort_field
    bool operator>=(const Entity& other) const {
        return get_attribute(m_sort_field) >= other.get_attribute(m_sort_field);
    }

    // Equality operator (==) based on m_sort_field
    bool operator==(const Entity& other) const {
        return get_attribute(m_sort_field) == other.get_attribute(m_sort_field);
    }

    // Inequality operator (!=) based on m_sort_field
    bool operator!=(const Entity& other) const {
        return get_attribute(m_sort_field) != other.get_attribute(m_sort_field);
    }

    // Overload << operator to print all attributes
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity) {
        for (const auto& pair : entity.m_attributes) {
            os << pair.second << '\t';
        }

        return os;
    }

    // Overload the extraction operator (>>) for your custom class
    friend std::istream& operator>>(std::istream& is, const Entity& entity) {
        for (const auto& pair : entity.m_attributes) {
            is << pair.second << '\t';
        }

        return is;
    }

    // Overload std::getline to extract data from a stream into an Entity
    friend std::istream& getline(std::istream& is, Entity& entity) {
        std::string line;
        if (std::getline(is, line)) {
            std::istringstream iss(line);
            KeyT key;
            DataT value;

            while (std::getline(iss, value, '\t')) {
                // Increment key for each value
                ++key;
                entity.set_attribute(key, value);
            }
        }

        return is;
    }
};


#endif //ASSIGNMENT4_ENTITY_H
