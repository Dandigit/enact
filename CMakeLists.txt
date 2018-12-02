cmake_minimum_required(VERSION 3.12)
project(enact)

set(CMAKE_CXX_STANDARD 14)

add_executable( enact
        src/Enact.cpp
        src/h/Enact.h
        src/h/common.h
        src/h/Token.h
        src/Scanner.cpp
        src/h/Scanner.h
        src/Chunk.cpp
        src/h/Chunk.h
        src/VM.cpp
        src/h/VM.h
        src/h/Compiler.h
        src/Compiler.cpp
        src/h/Value.h
        src/Value.cpp
        src/h/Object.h 
        src/Object.cpp 
        src/Environment.cpp 
        src/h/Environment.h 
        src/Allocator.cpp 
        src/h/Allocator.h 
        src/ast/Expr.h 
        src/ast/Stmt.h)
