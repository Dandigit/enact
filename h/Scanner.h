#ifndef MATILDA_SCANNER_H
#define MATILDA_SCANNER_H

#include <map>
#include <string>
#include <vector>

#include "Matilda.h"
#include "Token.h"
#include "Object.h"

using std::map;
using std::string;
using std::vector;

class Scanner : public Object {
    string m_source;
    vector<Token> m_tokens;

    uint32_t m_start = 0;
    uint32_t m_current = 0;
    uint32_t m_line = 1;

    int m_openParen = 0;

    void scanToken();

    void blockComment();
    void optionalSemicolon();

    void identifier();
    void number();
    void string();

    bool match(char expected);
    char peek() const;
    char peekNext() const;

    bool isAlpha(char c) const;
    bool isDigit(char c) const;
    bool isAlphaNumeric(char c) const;

    bool isAtEnd() const;
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, Object literal);

public:
    Scanner(::string source);

    vector<Token> scanTokens();
};


#endif //MATILDA_SCANNER_H
