// KeyValue Database

#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <type_traits>
#include <algorithm> // für std::remove
#include <cstring>   // für std::strncpy

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
        bool isNewKey = (store.find(key) == store.end());
        store[key] = value;

        if (isNewKey) {
            index[key.empty() ? '\0' : key[0]].push_back(key);
        }
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
        auto it = store.find(key);
        if (it != store.end()) {
            // Entferne aus Index
            char c = key.empty() ? '\0' : key[0];
            auto& vec = index[c];
            vec.erase(std::remove(vec.begin(), vec.end(), key), vec.end());
            if (vec.empty()) {
                index.erase(c);
            }

            // Entferne aus Store
            store.erase(it);
        }
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

        // Save index
        size_t indexCount = index.size();
        file.write(reinterpret_cast<const char*>(&indexCount), sizeof(indexCount));
        for (const auto& [c, keys] : index) {
            file.write(reinterpret_cast<const char*>(&c), sizeof(c));

            size_t vecSize = keys.size();
            file.write(reinterpret_cast<const char*>(&vecSize), sizeof(vecSize));

            for (const auto& k : keys) {
                size_t kSize = k.size();
                file.write(reinterpret_cast<const char*>(&kSize), sizeof(kSize));
                file.write(k.data(), kSize);
            }
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

        // Load number of entries
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

            store[key] = value;
        }

        // Load index
        size_t indexCount;
        file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));
        for (size_t i = 0; i < indexCount; ++i) {
            char c;
            file.read(reinterpret_cast<char*>(&c), sizeof(c));

            size_t vecSize;
            file.read(reinterpret_cast<char*>(&vecSize), sizeof(vecSize));

            std::vector<std::string> keys(vecSize);
            for (size_t j = 0; j < vecSize; ++j) {
                size_t kSize;
                file.read(reinterpret_cast<char*>(&kSize), sizeof(kSize));

                keys[j].resize(kSize);
                file.read(&keys[j][0], kSize);
            }

            index[c] = std::move(keys);
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
