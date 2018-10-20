#ifndef MATILDA_SCANNER_H
#define MATILDA_SCANNER_H

#include <map>
#include <string>
#include <vector>

#include "Token.h"

using std::map;
using std::string;
using std::vector;

class Scanner {
    string m_source;
    vector<Token> m_tokens;

public:
    Scanner(string source);

    vector<Token> scanTokens();
};


#endif //MATILDA_SCANNER_H
