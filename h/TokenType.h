#ifndef MATILDA_TOKENTYPE_H
#define MATILDA_TOKENTYPE_H


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
    IN, INT, NIL, OR, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    // End of file
    ENDFILE,
};

#endif //MATILDA_TOKENTYPE_H
