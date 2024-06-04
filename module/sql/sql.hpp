#ifndef SQL_HPP
#define SQL_HPP

#include <cstdlib>
#include <sqlite3.h>
#include <string>

/// This is a Database connection object.
/// NOTE that ONLY ONE connection a object should have in the same time. 
class Database {
private:

    /// The database connection object.
    sqlite3 * db;

    /// This string will be used to identify a Database obj.
    /// Every opened database has its own log.
    std::string dbName;
    std::string dbLogName;

public:

    /// NOTE: the callback function's first parameter should be void*,
    /// which is useless in most time.
    /// @brief: This function is to execute a SQL on the open database. It's a
    /// wrapper of the function sqlite3_exec().
    /// @param sql: SQL to execute
    /// @param callback: the function to process the data.
    /// @param errMsg
    int execSQL(
        std::string sql,                                /* SQL to execute */
        int (*callback)(void*, int, char**, char**),    /* callback func */
        char **errMsg
    ) {
        return sqlite3_exec(db, sql.c_str(), callback, NULL, errMsg);
    }
    /// @brief: This function is to execute a SQL on the open database. It's a
    /// wrapper of the function sqlite3_exec().
    /// @param sql: SQL to execute
    /// @param errMsg
    /// When sql will not output, use this function.
    int execSQL(
        std::string sql,                                /* SQL to execute */
        char **errMsg
    ) {
        return sqlite3_exec(db, sql.c_str(), NULL, NULL, errMsg);
    };

    /// The two functions initialize or open the database.
    /// NOTE: Use one of them once.
    /// NOTE: Please follow the output format!
    /// The format of the output is <time>\n<content>.
    /// Like this:
    /// Tue Jun  4 13:11:33 2024
    /// [[INFO]] : Open database database.db success

    /// Initialize the database with filename
    Database(std::string dbName);
    /// Initialize the database in RAM
    Database();
    
    ~Database() {
        sqlite3_close(db);
    }


};

/// This function prints the basic info of SQLite3.
/// version , sourceID
void print_sqlite_info();

#endif // !SQL_HPP