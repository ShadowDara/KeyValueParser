// Database for String and Integer KeyValue Map

#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <unordered_map>


namespace KeyValueDBSInt
{
    // Read a Map
    std::unordered_map<std::string, int32_t> read_map(const std::string& filename);

    // Save a Map
    void write_map(const std::unordered_map<std::string, int32_t>& map, const std::string& filename);
} // namespace KeyValueDBSInt
