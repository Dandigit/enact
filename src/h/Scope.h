#ifndef ENACT_ENVIRONMENT_H
#define ENACT_ENVIRONMENT_H

#include "Value.h"
#include "common.h"

#include <unordered_map>

struct Variable {
    Value value;
    bool isConst;
};

class Scope {
private:
    Scope *m_enclosing;
    std::unordered_map<std::string, index_t> m_indexes; // temp
public:
    explicit Scope(Scope* enclosing);
    index_t getIndex(const std::string &name);
    bool contains(const std::string &name);
    void set(const std::string &name, Value value);
    void create(const std::string &name, Variable variable);
};


#endif //ENACT_ENVIRONMENT_H
