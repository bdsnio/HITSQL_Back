#########################
# @date: 2024.6.4       #
# @author: Guo Yangfan  #
# @file: CMakeLists.txt #
#########################

# CMake Project settings
cmake_minimum_required (VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
project("hit-circle-backend")
set(PROJECT_NAME "hit-circle-backend")

# C Compiler settings
add_compile_options(-Werror -g)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsqlite3")
set(CMAKE_BUILD_TYPE Debug)                             # Type : Debug
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)   # Bin Path : bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)      # Lib Path : lib
set(RESC_DIR ${PROJECT_SOURCE_DIR}/resource)
set(MODULE_DIR ${PROJECT_SOURCE_DIR}/module)

# packages
find_package(Poco REQUIRED Crypto COMPONENTS Net XML)

# Compile and build
include_directories(
    ${Poco_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
## Static lib
add_subdirectory(${MODULE_DIR})

add_executable (${PROJECT_NAME} main.cpp ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    SQL
    cmdParser
    myLog
    httpServer
    PocoNet
    PocoUtil
    ${Poco_LIBRARIES}
)