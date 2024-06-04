#include "sql.hpp"
#include <sqlite3.h>
#include <iostream>
#include "../log/log.hpp"

#define SQLITE_ENABLE_COLUMN_METADATA 1

Database::Database(std::string dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::string errInfo =
            "[[ERROR]] : Open database " +
            std::string(sqlite3_errmsg(db));
        writeToLog("sql.log", errInfo);
    }
    else {
        std::string sucInfo =
            "[[INFO]] : Open database " + dbName + " success";
        writeToLog("sql.log", sucInfo);
    }
}

Database::Database() {
    if (sqlite3_open(NULL, &db)) {
        std::string errInfo =
            "[[ERROR]] : Open database " +
            std::string(sqlite3_errmsg(db));
        writeToLog("sql.log", errInfo);
    }
    else {
        std::string sucInfo =
            "[[INFO]] : Open database in RAM success";
        writeToLog("sql.log", sucInfo);
    }
}

void print_sqlite_info() {
    // Print sqlite3 version info
    std::cout << "[[INFO]] : Sqlite3 version: " << sqlite3_libversion() <<std::endl;
    std::cout << "[[INFO]] : Sqlite3 sourceID: " << sqlite3_sourceid() << std::endl;
}