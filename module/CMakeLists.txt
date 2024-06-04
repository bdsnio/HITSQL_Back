add_library(myLog STATIC
    ${MODULE_DIR}/log/log.cpp
)
add_library(theSqlite STATIC
    ${MODULE_DIR}/sql/sqlite3.c
)
add_library(SQL STATIC
    ${MODULE_DIR}/sql/sql.cpp
)
target_link_libraries(SQL
    theSqlite
)

add_library(cmdParser STATIC
    ${MODULE_DIR}/cmdParser/parser.cpp
)