#>>>>>>>>>>>myLog<<<<<<<
add_library(myLog SHARED
    ${MODULE_DIR}/log/log.cpp
)
#>>>>>>>>>>>theSqlite<<<<<<<
add_library(theSqlite SHARED
    ${MODULE_DIR}/sql/sqlite3.c
)
#>>>>>>>>>>>myConfig<<<<<<<
add_library(myConfig SHARED
    ${MODULE_DIR}/config/config.cpp
)
#>>>>>>>>>>>SQL<<<<<<<
add_library(SQL SHARED
    ${MODULE_DIR}/sql/sql.cpp
)
target_link_libraries(SQL
    theSqlite
    myConfig
    myLog
)
#>>>>>>>>>>>cmdParser<<<<<<<
add_library(cmdParser SHARED
    ${MODULE_DIR}/cmdParser/parser.cpp
)
#>>>>>>>>>>>httpServer<<<<<<<
add_library(httpServer SHARED
    ${MODULE_DIR}/http/http.cpp
    ${MODULE_DIR}/http/mainFactory.cpp
)
target_link_libraries(
    httpServer
    myConfig
    PocoNet
    PocoUtil
    ${Poco_LIBRARIES}
)