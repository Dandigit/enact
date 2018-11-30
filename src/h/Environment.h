#ifndef MATILDA_ENVIRONMENT_H
#define MATILDA_ENVIRONMENT_H

#include "Value.h"

#include <unordered_map>

class Environment {
private:
    Environment *m_enclosing;
    std::unordered_map<std::string, Value> m_variables;
public:
    Environment(Environment* enclosing);
    Value find(const std::string &name);
    bool contains(const std::string &name);
    void set(const std::string &name, Value value);
    void create(const std::string &name, Value value);
};


#endif //MATILDA_ENVIRONMENT_H
