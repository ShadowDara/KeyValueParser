#pragma once

#include <string>
#include <vector>


// // Speichern
// void writeString(std::ofstream& file, const std::string& str) {
//     size_t len = str.size();
//     file.write(reinterpret_cast<const char*>(&len), sizeof(len));
//     file.write(str.data(), len);
// }

// // Laden
// std::string readString(std::ifstream& file) {
//     size_t len;
//     file.read(reinterpret_cast<char*>(&len), sizeof(len));
//     std::string str(len, '\0');
//     file.read(&str[0], len);
//     return str;
// }

// template<typename T>
// void writeVector(std::ofstream& file, const std::vector<T>& vec) {
//     size_t len = vec.size();
//     file.write(reinterpret_cast<const char*>(&len), sizeof(len));
//     if (!vec.empty()) {
//         file.write(reinterpret_cast<const char*>(vec.data()), len * sizeof(T));
//     }
// }

// template<typename T>
// std::vector<T> readVector(std::ifstream& file) {
//     size_t len;
//     file.read(reinterpret_cast<char*>(&len), sizeof(len));
//     std::vector<T> vec(len);
//     if (!vec.empty()) {
//         file.read(reinterpret_cast<char*>(vec.data()), len * sizeof(T));
//     }
//     return vec;
// }
