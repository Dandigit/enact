cmake_minimum_required(VERSION 3.12)
project(matilda)

set(CMAKE_CXX_STANDARD 14)

add_executable(matilda src/main.cpp h/TokenType.h h/Token.h)