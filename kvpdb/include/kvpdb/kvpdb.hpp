// KeyValue Database

#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>


struct default_db_struct
{
    std::string tempname = "default";

    default_db_struct() = default;
    default_db_struct(const std::string& name) : tempname(name) {}
};


template <typename DBStruct = default_db_struct>
class KeyValueDB {
private:
    std::unordered_map<std::string, DBStruct> store;

    // Optional: einfacher sekundärer Index (z.B. nach erstem Buchstaben)
    std::unordered_map<char, std::vector<std::string>> index;

public:
    // Insert / Update
    void put(const std::string& key, DBStruct& value)
    {
        store[key] = value;
        index[key[0]].push_back(key);
    }

    // Read
    bool get(const std::string& key, DBStruct& value) const
    {
        auto it = store.find(key);
        if (it != store.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    // Delete
    void remove(const std::string& key)
    {
        store.erase(key);
        // Index wird hier nicht bereinigt (vereinfachte Version)
    }

    // Save to file
    void save(const std::string& filename) const
    {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Fehler beim Öffnen der Datei zum Schreiben\n";
            return;
        }

        for (const auto& pair : store) {
            file << pair.first << "=" << pair.second << "\n";
        }
    }

    // Load from file
    void load(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Fehler beim Öffnen der Datei zum Lesen\n";
            return;
        }

        store.clear();
        index.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string key, value;

            if (std::getline(ss, key, '=') && std::getline(ss, value)) {
                put(key, value);
            }
        }
    }

    // Get keys by first character (for testing)
    std::vector<std::string> getByFirstChar(char c)
    {
        if (index.find(c) != index.end()) {
            return index[c];
        }
        return {};
    }

    // Print all key-value pairs (for testing)
    void printAll() const
    {
        for (const auto& pair : store) {
            std::cout << pair.first << " => " << pair.second << "\n";
        }
    }
};
