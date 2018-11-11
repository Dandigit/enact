//
// Created by dan on 11/11/18.
//

#ifndef GVM_SCANNER_H
#define GVM_SCANNER_H

#include <string>

#include "Token.h"

class Scanner {
private:
    std::string m_source;
    size_t m_start, m_current = 0;

    line_t m_line = 1;
    col_t m_col = 0;

    Token number();
    Token identifier();
    Token string();

    TokenType identifierType(std::string candidate);

    Token makeToken(TokenType type);
    Token errorToken(const std::string &what);

    void skipWhitespace();

    bool isAtEnd();
    char advance();
    char peek();
    char peekNext();
    bool match(char expected);

    bool isDigit(char c);
    bool isIdentifierStart(char c);
    bool isIdentifier(char c);
public:
    Scanner(std::string source);
    ~Scanner() = default;

    Token scanToken();


};


#endif //GVM_SCANNER_H