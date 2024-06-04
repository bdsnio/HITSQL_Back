#ifndef SQL_HPP
#define SQL_HPP

#include <cstdlib>
#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3 * db;

public:

    /// The two functions initialize or open the database.
    /// NOTE: Please follow the output format!
    /// The format of the output is <time>\n<content>.
    /// Like this:
    /// Tue Jun  4 13:11:33 2024
    /// [[INFO]] : Open database database.db success

    /// Initialize the database with filename
    Database(std::string dbName);
    /// Initialize the database in RAM
    Database();
    
    ~Database() {}


};

/// This function prints the basic info of SQLite3.
/// version , sourceID
void print_sqlite_info();

#endif // !SQL_HPP