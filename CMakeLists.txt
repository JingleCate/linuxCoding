cmake_minimum_required(VERSION 3.24)
project(BaseTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(BaseTest main.cpp
        sources/include/fd.h
        sources/fd.cpp
        sources/include/proc.h
        sources/proc.cpp
        sources/socket.cpp
        sources/include/socket.h
        sources/include/cxx11.h
        sources/cxx11.cpp sources/include/slc.h)
