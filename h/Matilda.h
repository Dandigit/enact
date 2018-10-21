#ifndef MATILDA_MATILDA_H
#define MATILDA_MATILDA_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Token.h"
#include "Scanner.h"

using std::ifstream;
using std::vector;

enum class ExitCode {
    INVALID_ARGUMENTS = 65,
    FILE_ERROR = 70,
    STATIC_ERROR = 75,
};

class Matilda {
    static void report(uint32_t line, std::string where, std::string message);

public:

    static bool hadError;

    Matilda() { hadError = false; }

    static void run(std::string source);
    static void runFile(std::string path);
    static void runPrompt();
    static void error(uint32_t line, std::string message);
    static void start(int argc, char *argv[]);
};

int main(int argc, char *argv[]);

#endif //MATILDA_MATILDA_H
