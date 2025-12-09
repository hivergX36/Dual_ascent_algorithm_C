#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <algorithm>



template <typename Key, typename Value>
class Dictionnary
{

    private: 

    // Size in fonction of the degree of the polynomial


    int hashFunction(const Key &key)
    {
        int hashValue = 0;
        for (char ch : key)
        {
            hashValue += int(ch);
        }
        return hashValue % table_size;
    }

    public:

    int table_size;
    std::vector<std::pair<Key, Value>> *dictionnary;

    Dictionnary(int size)
    {
        table_size = size;
        dictionnary = new std::vector<std::pair<Key, Value>>[table_size];
    }

    void insert(const Key &key, const Value &value)
    {
        int index = hashFunction(key);
        for (auto &pair : dictionnary[index])
        {
            if (pair.first == key)
            {
                pair.second = value;
                return;
            }
        }
        dictionnary[index].push_back({key, value});
    }

    void delete_key(const Key &key)
    {
        int index = hashFunction(key);
        auto &vector = dictionnary[index];
        for (auto el = vector.begin(); el != vector.end(); ++el)
        {
            if (el->first == key)
            {
                vector.erase(el);
                return;
            }
        }
    }

    void display_value(const Key &key)
    {
        int index = hashFunction(key);
        for (auto &pair : dictionnary[index])
        {
            if (pair.first == key)
            {
                std::cout << "Value: " << pair.second << std::endl;
                return;
            }
        }
        std::cout << "Key not found" << std::endl;
    }

    Value return_value(const Key &key)
    {
        int index = hashFunction(key);
        for (auto &pair : dictionnary[index]) {
                 if (pair.first == key)
                 {
                     return pair.second;
                 }
             }
    }

    void dictionnary_diplay_key_value()
    {
        for (int i = 0; i < table_size; ++i)
        {
            for (auto &pair : dictionnary[i])
            {
                std::cout << "Key: " << pair.first << " Value: " << pair.second << std::endl;
            }
        }
    std::cout << "end of display" << std::endl;

    }
};
