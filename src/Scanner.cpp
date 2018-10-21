#include "../h/Scanner.h"

std::map<std::string, TokenType> Scanner::m_keywords = {
        {"and",     AND},
        {"bool",    BOOL},
        {"class",   CLASS},
        {"const",   CONST},
        {"dub",     DUB},
        {"else",    ELSE},
        {"end",     END},
        {"false",   FALSE},
        {"fun",     FUN},
        {"for",     FOR},
        {"if",      IF},
        {"int",     INT},
        {"nil",     NIL},
        {"or",      OR},
        {"return",  RETURN},
        {"super",   SUPER},
        {"this",    THIS},
        {"true",    TRUE},
        {"var",     VAR},
        {"while",   WHILE}
};


Scanner::Scanner(std::string source) :
    m_source { source } {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        // We're at the beginning of the next lexeme
        scanToken();
        m_start = m_current;
    }

    m_tokens.push_back(Token{ ENDFILE, "", m_line, "" });
    return m_tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        // Single character tokens
        case '(': addToken(LEFT_PAREN); ++m_openParen; break;
        case ')': addToken(RIGHT_PAREN); --m_openParen; break;
        case '[': addToken(LEFT_SQUARE); ++m_openParen; break;
        case ']': addToken(RIGHT_SQUARE); --m_openParen; break;
        case ':': addToken(COLON); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;
        case '?': addToken(QUESTION); break;

        // One or two characters
        case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
        case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
        case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
        case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;

        // Handle comments or slash
        case '/':
            // Single line comment
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            // Block comment
            } else if (match('*')) {
                blockComment();
            // Plain ol' slash
            } else {
                addToken(SLASH);
            }
            break;

        // Ignore whitespace
        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            ++m_line;
            optionalSemicolon();
            break;

        case '"': string(); break;

        // Not allowed
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                std::string errorMessage {"Unexpected character '"};
                errorMessage += c;
                errorMessage += "'.";
                Matilda::error(m_line, errorMessage);
                break;
            }
    }
}

void Scanner::optionalSemicolon() {

}

void Scanner::blockComment() {

}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();

    std::string text {m_source.substr(m_start, m_current - m_start)};
    // Default to IDENTIFIER, if we don't match a keyword, we know that this token is an identifier.
    TokenType type {IDENTIFIER};

    // Check if the matched word is a keyword
    if (m_keywords.count(text) != 0) {
        type = m_keywords[text];
    }

    addToken(type);
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Eat the '.'
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(NUMBER,
            m_source.substr(m_start, m_current - m_start));
}

void Scanner::string() {
    std::string value = "";

    while (peek() != '"' && !isAtEnd()) {
        value += peek();
        if (peek() == '\n') ++m_line;
        advance();
    }

    // Unterminated string.
    if (isAtEnd()) {
        Matilda::error(m_line, "Unterminated string.");
        return;
    }

    // Close quote.
    advance();

    addToken(STRING, value);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (m_source[m_current] != expected) return false;

    ++m_current;
    return true;
}

char Scanner::peek() const {
    if (isAtEnd()) return '\0';
    return m_source[m_current];
}

char Scanner::peekNext() const {
    if (m_current + 1 >= m_source.length()) return '\0';
    return m_source[m_current + 1];
}

bool Scanner::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Scanner::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

bool Scanner::isAtEnd() const {
    return m_current >= m_source.length();
}

char Scanner::advance() {
    return m_source[m_current++];
}

void Scanner::addToken(TokenType type) {
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal) {
    std::string lexeme = m_source.substr(m_start, m_current - m_start);
    m_tokens.push_back(Token{type, lexeme, m_line, literal});
}