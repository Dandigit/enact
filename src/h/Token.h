//
// Created by dan on 11/11/18.
//

#ifndef GVM_TOKEN_H
#define GVM_TOKEN_H

#include "common.h"

#include <iostream>

enum class TokenType {
    // Single character tokens.
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_SQUARE, RIGHT_SQUARE,
    COLON, COMMA, DOT, MINUS, PLUS,
    QUESTION, SEMICOLON, SLASH, STAR,

    // 1 or 2 character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Reserved words.
    AND, BOOL, CLASS, CONST, ELSE, END, FALSE, FUN, FOR,
    IF, NIL, OR, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    ERROR, ENDFILE,
};

struct Token {
    TokenType type;
    std::string lexeme;
    line_t line;
    col_t col;
};


#endif //GVM_TOKEN_H
