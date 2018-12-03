#ifndef ENACT_ENVIRONMENT_H
#define ENACT_ENVIRONMENT_H

#include "Value.h"

#include <unordered_map>

struct Variable {
    Value value;
    bool isConst;
};

class Environment {
private:
    Environment *m_enclosing;
    std::unordered_map<std::string, Variable> m_variables;
public:
    explicit Environment(Environment* enclosing);
    Variable find(const std::string &name);
    bool contains(const std::string &name);
    void set(const std::string &name, Value value);
    void create(const std::string &name, Variable variable);
};


#endif //ENACT_ENVIRONMENT_H
