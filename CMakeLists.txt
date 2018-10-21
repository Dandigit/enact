cmake_minimum_required(VERSION 3.12)
project(matilda)

set(CMAKE_CXX_STANDARD 14)

add_executable(matilda src/Matilda.cpp h/TokenType.h src/Token.cpp h/Token.h src/Scanner.cpp h/Scanner.h h/Matilda.h)