cmake_minimum_required(VERSION 3.13)
project(semestral)

set(CMAKE_CXX_STANDARD 14)

add_executable(semestral main.cpp CCell.cpp CCell.h CFunction.cpp CFunction.h CString.cpp CString.h CNumber.cpp CNumber.h)