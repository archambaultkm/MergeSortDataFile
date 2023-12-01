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
    int m_sort_field = 14;

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

    template <typename Compare>
    bool compare_attributes(const Entity& other, Compare comp) const {
        try {
            return comp(get_attribute(m_sort_field), other.get_attribute(m_sort_field));
        } catch (const std::out_of_range&) {
            // Consider uninitialized entities, or those without data at that key, less than
            return true;
        }
    }

    // Comparison operator (<) based on m_sort_field
    bool operator<(const Entity& other) const {
        return compare_attributes(other, std::less<DataT>());
    }

    // Comparison operator (<=) based on m_sort_field
    bool operator<=(const Entity& other) const {
        return compare_attributes(other, std::less_equal<DataT>());
    }

    // Comparison operator (>) based on m_sort_field
    bool operator>(const Entity& other) const {
        return compare_attributes(other, std::greater<DataT>());
    }

    // Comparison operator (>=) based on m_sort_field
    bool operator>=(const Entity& other) const {
        return compare_attributes(other, std::greater_equal<DataT>());
    }

    // Equality operator (==) based on m_sort_field
    bool operator==(const Entity& other) const {
        return compare_attributes(other, std::equal_to<DataT>());
    }

    // Inequality operator (!=) based on m_sort_field
    bool operator!=(const Entity& other) const {
        return compare_attributes(other, std::not_equal_to<DataT>());
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
            KeyT key = 1;
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


#endif //ASSIGNMENT4_ENTITY_H
