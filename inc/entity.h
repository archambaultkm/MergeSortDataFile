//
// Created by Kaitlyn Archambault on 2023-11-27.
//

#ifndef ASSIGNMENT4_ENTITY_H
#define ASSIGNMENT4_ENTITY_H

#include <map>

template <typename KeyT, typename DataT>
class Entity {
private:
    std::map<KeyT, DataT> m_attributes;

public:
    void set_attribute(KeyT key, const DataT& value) {
        m_attributes[key] = value;
    }

    DataT get_attribute(int key) const {
        auto iter = m_attributes.find(key);

        if (iter != m_attributes.end()) {

            return iter->second;

        } else {
            // handle the case when the key is not found
            throw std::out_of_range("Key not found");
        }
    }

    // Overload << operator to print all attributes
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity) {
        for (const auto& pair : entity.m_attributes) {
            os << pair.second << '\t';
            // TODO it would be nice to specify delimiter especially for saving to file
        }
        return os;
    }
};


#endif //ASSIGNMENT4_ENTITY_H
