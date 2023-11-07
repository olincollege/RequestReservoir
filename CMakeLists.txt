cmake_minimum_required(VERSION 3.10)

project(HTTPServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(HTTPServer src/main.c)

target_include_directories(HTTPServer PRIVATE ${CMAKE_SOURCE_DIR}/include)


