#ifndef MATILDA_TOKENTYPE_H
#define MATILDA_TOKENTYPE_H

#include <string>

enum TokenType {
    // Single character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_SQUARE, RIGHT_SQUARE, COLON,
    COMMA, DOT, MINUS, PLUS, QUESTION, SEMICOLON, SLASH, STAR,

    // 1 or 2 character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Reserved words
    AND, BOOL, CLASS, DUB, ELSE, END, FALSE, FUN, FOR, IF,
    INT, NIL, OR, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    // End of file
    ENDFILE,
};

std::string toString(TokenType type) {
    switch (type) {
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case LEFT_SQUARE: return "LEFT_SQUARE";
        case RIGHT_SQUARE: return "RIGHT_SQUARE";
        case COLON: return "COLON";
        case COMMA: return "COMMA";
        case DOT: return "DOT";
        case MINUS: return "MINUS";
        case PLUS: return "PLUS";
        case QUESTION: return "QUESTION";
        case SEMICOLON: return "SEMICOLON";
        case SLASH: return "SLASH";
        case STAR: return "STAR";
        case BANG: return "BANG";
        case BANG_EQUAL: return "BANG_EQUAL";
        case EQUAL: return "EQUAL";
        case EQUAL_EQUAL: return "EQUAL_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";
        case IDENTIFIER: return "IDENTIFIER";
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";
        case AND: return "AND";
        case BOOL: return "BOOL";
        case CLASS: return "CLASS";
        case DUB: return "DUB";
        case ELSE: return "ELSE";
        case END: return "END";
        case FALSE: return "FALSE";
        case FUN: return "FUN";
        case FOR: return "FOR";
        case IF: return "IF";
        case INT: return "INT";
        case NIL: return "NIT";
        case OR: return "OR";
        case RETURN: return "RETURN";
        case SUPER: return "SUPER";
        case THIS: return "THIS";
        case TRUE: return "TRUE";
        case VAR: return "VAR";
        case WHILE: return "WHILE";
        case ENDFILE: return "ENDFILE";
    }
}

#endif //MATILDA_TOKENTYPE_H
