cmake_minimum_required(VERSION 3.12)
project(matilda)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        matilda
        src/Matilda.cpp
        src/h/Matilda.h
        src/h/common.h
        src/h/Token.h
        src/Scanner.cpp
        src/h/Scanner.h
        src/Chunk.cpp
        src/h/Chunk.h
        src/VM.cpp
        src/h/VM.h
        src/h/Compiler.h src/Compiler.cpp src/h/Value.h src/Value.cpp src/h/Object.h src/Object.cpp)