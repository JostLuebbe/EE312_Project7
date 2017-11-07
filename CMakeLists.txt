cmake_minimum_required(VERSION 3.6)
project(Project7)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Project7.cpp Customer.h CustomerDB.cpp CustomerDB.h String.h)
add_executable(Project7 ${SOURCE_FILES})