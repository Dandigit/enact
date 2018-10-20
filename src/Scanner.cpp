#include "../h/Scanner.h"

Scanner::Scanner(string source) :
    m_source { source }, m_start {0}, m_current {0}, m_line{1} {}

vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        // We're at the beginning of the next lexeme
        m_start = m_current;
        scanToken();
    }

    m_tokens.push_back(Token{ ENDFILE, "", m_line });
    return m_tokens;
}

void Scanner::scanTokens() {
    char c = advance();
    switch (c) {
        // Single character tokens
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '[': addToken(LEFT_SQUARE); break;
        case ']': addToken(RIGHT_SQUARE); break;
        case ':': addToken(COLON); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;

        // One or two characters
        case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
        case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
        case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
        case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;

        // Not allowed
        case '~':
        case '@':
        case '#':
        case '$':
        case '^':
        case '&':
        case '{':
        case '}':
        case '|':
        case '`':
            Matilda::error(m_line, "Unexpected character '" + c + "'.");
            break;
    }
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (m_source.at(m_current) != expected) return false;

    ++m_current;
    return true;
}

bool Scanner::isAtEnd() const {
    return m_current >= m_source.length();
}

char Scanner::advance() {
    return m_source.at(m_current++);
}

void Scanner::addToken(TokenType type) {
    string lexeme = m_source.substr(m_start, m_current);
    m_tokens.push_back(Token{type, lexeme, m_line});
}