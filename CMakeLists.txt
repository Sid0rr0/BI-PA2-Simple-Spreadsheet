cmake_minimum_required(VERSION 3.13)
project(lethanhh)

set(CMAKE_CXX_FLAGS "-lncurses")

set(CMAKE_CXX_STANDARD 14)

add_executable(lethanhh src/main.cpp src/CCell.cpp src/CCell.h src/CFunction.cpp src/CFunction.h src/CString.cpp src/CString.h src/CNumber.cpp
        src/CNumber.h src/COperation.cpp src/COperation.h src/CTable.cpp src/CTable.h src/CCursor.cpp src/CCursor.h)