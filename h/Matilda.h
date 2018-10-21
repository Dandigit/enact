#ifndef MATILDA_MATILDA_H
#define MATILDA_MATILDA_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Object.h"

using std::ifstream;
using std::string;
using std::vector;

enum class ExitCode {
    INVALID_ARGUMENTS = 65,
    FILE_ERROR = 70,
    STATIC_ERROR = 75,
};

class Matilda : public Object {
    static void report(uint32_t line, string where, string message);

public:

    static bool hadError;

    Matilda() { hadError = false; }

    static void run(string source);
    static void runFile(string path);
    static void runPrompt();
    static void error(uint32_t line, string message);
    static void start(int argc, char *argv[]);
};

int main(int argc, char *argv[]);

#endif //MATILDA_MATILDA_H
