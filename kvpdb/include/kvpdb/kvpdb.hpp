// KeyValue Database

#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <type_traits>
#include <cstring>

#include <kvpdb/kvpdb_internal.hpp>


// Beispielstruktur für die Werte
struct default_db_struct
{
    char tempname[8] = "default";

    default_db_struct() = default;
    default_db_struct(const std::string& name) : tempname()
    {
        std::strncpy(tempname, name.c_str(), sizeof(tempname) - 1);
        tempname[sizeof(tempname) - 1] = '\0';
    }

    friend std::ostream& operator<<(std::ostream& os, const default_db_struct& obj)
    {
        os << obj.tempname;
        return os;
    }
};


// Einfaches Key-Value Store mit Binary-Speicherung
template <typename DBStruct = default_db_struct>
class KeyValueDB {
private:
    std::unordered_map<std::string, DBStruct> store;

    // Optional: einfacher sekundärer Index (z.B. nach erstem Buchstaben)
    std::unordered_map<char, std::vector<std::string>> index;

public:
    // Insert / Update
    void put(const std::string& key, const DBStruct& value)
    {
        if (store.find(key) == store.end()) {
            index[key.empty() ? '\0' : key[0]].push_back(key);
        }
        store[key] = value;
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

    // Save to file as Binary
    void save(const std::string& filename) const
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Fehler beim Öffnen der Datei zum Schreiben\n";
            return;
        }

        // Save number of entries
        size_t count = store.size();
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));

        // Save Entries
        for (const auto& [key, value] : store) {
            size_t keySize = key.size();
            file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
            file.write(key.data(), keySize);

            // Value als Binary speichern
            file.write(reinterpret_cast<const char*>(&value), sizeof(DBStruct));
        }
    }

    // Load from file as Binary
    void load(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Fehler beim Öffnen der Datei zum Lesen\n";
            return;
        }

        store.clear();
        index.clear();

        // Load Number of entries
        size_t count;
        file.read(reinterpret_cast<char*>(&count), sizeof(count));

        // Load Entries
            for (size_t i = 0; i < count; ++i) {
            size_t keySize;
            file.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));

            std::string key(keySize, '\0');
            file.read(&key[0], keySize);

            DBStruct value;
            file.read(reinterpret_cast<char*>(&value), sizeof(DBStruct));

            put(key, value);
        }
    }

    // Get keys by first character (for testing)
    std::vector<std::string> getByFirstChar(char c) const
    {
        auto it = index.find(c);
        if (it != index.end()) {
            return it->second;
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
