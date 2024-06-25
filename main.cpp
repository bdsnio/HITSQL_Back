#include <iostream>
#include "include/cmdline.h"
#include "module/config/config.hpp"
#include "module/cmdParser/parser.hpp"
#include "module/sql/sql.hpp"
#include "module/http/http.hpp"

int main(int argc, char * argv[])
{
    Config::configInit();
    Config::getInstance().configParse("config/config.toml");
    
    cmdline::parser argParser =  argParse(argc, argv);

    if (argParser.exist("init")) {
        std::cout << "[[INFO]] : Initialize the database..." << std::endl;
        // Initialize the database.
        Database DB("database.db");
        initSQLite(DB);
    }
    if (argParser.exist("start")) {
        std::cout << "[[INFO]] : HIT-Circle-backend Starting..." << std::endl;
        print_sqlite_info();
        // Connect the database.
        Database DB("database.db");
        // start server
        ServerApp serverapp;
        serverapp.run(argc-1, argv++);
    }
    if (argc == 1) {
        std::cout << argParser.usage();
    }

    Config::configQuit();
    return 0;
}