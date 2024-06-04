#include "sql.hpp"
#include <sqlite3.h>
#include <iostream>

#define SQLITE_ENABLE_COLUMN_METADATA 1

void print_sqlite_info() {
    // Print sqlite3 version info
    std::cout << "Sqlite3 version: " << sqlite3_libversion() <<std::endl;
    std::cout << "Sqlite3 sourceID: " << sqlite3_sourceid() << std::endl;
}