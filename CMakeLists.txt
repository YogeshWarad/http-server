cmake_minimum_required(VERSION 3.14)
project(http_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(http_server
    src/main.cpp
    src/server.cpp
    src/connection.cpp
    src/router.cpp
)

# Unit Tests
enable_testing()
add_subdirectory(tests)
