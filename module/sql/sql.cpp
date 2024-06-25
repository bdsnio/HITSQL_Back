#include "sql.hpp"
#include "../config/config.hpp"
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

#define SQLITE_ENABLE_COLUMN_METADATA 1

Database::Database(std::string dbName) {
  dbLogName = dbName + "_sql.log";
  if (sqlite3_open(dbName.c_str(), &db)) {
    std::string errInfo =
        "[[ERROR]] : Open database " + std::string(sqlite3_errmsg(db));
    writeToLog(dbLogName, errInfo);
  } else {
    std::string sucInfo = "[[INFO]] : Open database " + dbName + " success";
    writeToLog(dbLogName, sucInfo);
  }
}

Database::Database() {
  dbLogName = "RAM_sql.log";
  if (sqlite3_open(NULL, &db)) {
    std::string errInfo =
        "[[ERROR]] : Open database " + std::string(sqlite3_errmsg(db));
    writeToLog(dbLogName, errInfo);
  } else {
    std::string sucInfo = "[[INFO]] : Open database in RAM success";
    writeToLog(dbLogName, sucInfo);
  }
}

void print_sqlite_info() {
  // Print sqlite3 version info
  std::cout << "[[INFO]] : Sqlite3 version: " << sqlite3_libversion()
            << std::endl;
  std::cout << "[[INFO]] : Sqlite3 sourceID: " << sqlite3_sourceid()
            << std::endl;
}

void initSQLite(Database DB_) {
  auto config = Config::getInstance().getConfig();
  std::vector<std::string> initSQLs;
  auto config_arrays = config.at_path("database.initSQLs").as_array();
  for (auto &sql : *config_arrays) {
    initSQLs.push_back(sql.value<std::string>().value());
  }

  char *errMsg = 0;
  for (auto &sql : initSQLs) {
    DB_.execSQL(sql);
  }
}