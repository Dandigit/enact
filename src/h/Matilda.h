//
// Created by dan on 11/11/18.
//

#ifndef GVM_MATILDA_H
#define GVM_MATILDA_H

#include <string>

enum class ExitCode {
    INVALID_ARGUMENTS = 65,
    FILE_ERROR = 70,
    STATIC_ERROR = 75,
};

class Matilda {
private:
    static void report(uint32_t line, std::string where, std::string message);
public:
    static bool hadError;

    static void run(std::string source);
    static void runFile(std::string path);
    static void runPrompt();
    static void error(uint32_t line, std::string message);
    static void start(int argc, char *argv[]);
};

int main(int argc, char *argv[]);

#endif //GVM_MATILDA_H
