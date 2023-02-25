cmake_minimum_required(VERSION 3.24)
project(BaseTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(BaseTest main.cpp sources/fd.h sources/fd.cpp)
