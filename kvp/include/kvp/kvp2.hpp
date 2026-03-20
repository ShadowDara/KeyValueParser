// Newer KeyValue Parser with Temapltes
//
// LICENSE: MIT Shadowdara 2026
// DO NOT REMOVE THIS INFO
//

#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <sstream>
#include <string_view>
#include <iostream>

#include <kvp/kvp.hpp>


// Namespace for the Template Based Version
namespace KeyValueParser2 {

    // --- Thin template-based store ---
    template <typename MapType = std::unordered_map<std::string, std::string>>
    class KeyValueStore
    {
        MapType data;

    public:
        KeyValueStore() = default;
        KeyValueStore(const MapType& init) : data(init) {}

        // Funtion to set a Value
        void set(const std::string& key, const std::string& value)
        {
            data[key] = value;
        }

        // Function to get a Value
        std::optional<std::string> get(const std::string& key) const 

            auto it = data.find(key);
            if (it != data.end()) return it->second;
            return std::nullopt;
        }

        // Function to delete a Value
        void erase(const std::string& key)
        {
            data.erase(key);
        }

        // Function to check if an entry in contained
        bool contains(const std::string& key) const
        {
            return data.find(key) != data.end();
        }

        const MapType& get_data() const
        {
            return data;
        }
    };

    // --- Parser functions ---
    template <typename StoreType>
    StoreType parse_kvp2(const std::string& input) {
        StoreType store;
        std::stringstream ss(input);
        std::string line;

        while (std::getline(ss, line)) {
            if (line.empty() || line.starts_with('#')) continue;

            std::string_view line_view(line);
            auto pos = line_view.find('=');
            if (pos == std::string_view::npos) continue;

            std::string_view key = trim_view(line_view.substr(0, pos));
            std::string_view value = trim_view(line_view.substr(pos + 1));

            if (!store.contains(std::string(key))) {
                store.set(std::string(key), std::string(value));
            }
            else {
                std::cerr << "Duplicate key found: " << key << "\n";
            }
        }
        return store;
    }

    // --- Writer functions operating on store ---
    template <typename StoreType>
    void append_entry(StoreType& store, const std::string& key, const std::string& value) {
        if (!store.contains(key)) {
            store.set(key, value);
        }
        else {
            std::cerr << "Entry already exists!: " << key << " Value: " << value << "\n";
        }
    }

    template <typename StoreType>
    void overwrite_entry(StoreType& store, const std::string& key, const std::string& value) {
        if (store.contains(key)) {
            store.set(key, value);
        }
        else {
            std::cerr << "Entry does not exist!: " << key << "\n";
        }
    }

    template <typename StoreType>
    void delete_entry(StoreType& store, const std::string& key) {
        if (store.contains(key)) {
            store.erase(key);
        }
        else {
            std::cerr << "Entry does not exist!: " << key << "\n";
        }
    }

    // --- Writer functions operating on strings ---
    inline std::string append_entry(const std::string& key, const std::string& value, const std::string& input) {
        return input + "\n" + key + "=" + value;
    }

    inline std::string overwrite_entry(const std::string& key, const std::string& value, const std::string& input) {
        std::stringstream ss(input);
        std::string line;
        std::string output;
        bool replaced = false;

        while (std::getline(ss, line)) {
            if (line.empty() || line.starts_with('#')) {
                output += line + "\n";
                continue;
            }

            auto pos = line.find('=');
            if (pos != std::string::npos) {
                std::string cur_key = line.substr(0, pos);
                if (cur_key == key) {
                    line = key + "=" + value;
                    replaced = true;
                }
            }
            output += line + "\n";
        }

        if (!replaced) output += key + "=" + value + "\n";
        return output;
    }

    inline std::string delete_entry(const std::string& key, const std::string& input) {
        std::stringstream ss(input);
        std::string line;
        std::string output;

        while (std::getline(ss, line)) {
            if (line.empty() || line.starts_with('#')) {
                output += line + "\n";
                continue;
            }

            auto pos = line.find('=');
            if (pos != std::string::npos) {
                std::string cur_key = line.substr(0, pos);
                if (cur_key == key) continue;
            }
            output += line + "\n";
        }

        return output;
    }

} // namespace KeyValueParser
