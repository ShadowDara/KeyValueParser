#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

#include <kvpdb/kvpdb.hpp>

//using namespace kvpdb;


int main() {
    KeyValueDB<default_db_struct> db;

    db.put("apple", default_db_struct("fruit"));
    db.put("banana", default_db_struct("fruit"));
    db.put("carrot", default_db_struct("vegetable"));

    std::cout << "Initial DB:\n";
    db.printAll();

    db.save("db.txt");

    KeyValueDB<default_db_struct> db2;
    db2.load("db.txt");

    std::cout << "\nGeladene DB:\n";
    db2.printAll();

    default_db_struct value;
    if (db2.get("apple", value)) {
        std::cout << "\napple => " << value.tempname << "\n";
    }

    std::cout << "\nIndex (a):\n";
    for (const auto& key : db2.getByFirstChar('a')) {
        std::cout << key << "\n";
    }

    return 0;
}
