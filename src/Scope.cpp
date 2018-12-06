#include "h/Scope.h"

Scope::Scope(Scope *enclosing) : m_enclosing{enclosing} {}

Variable Scope::find(const std::string &name) {
    return m_variables[name];
}

bool Scope::contains(const std::string &name) {
    if (m_variables.count(name) > 0) {
        return true;
    }

    if (m_enclosing) return m_enclosing->contains(name);
    return false;
}

void Scope::set(const std::string &name, Value value) {
    if (m_variables.count(name) > 0) {
        m_variables[name].value = value;
    }

    if (m_enclosing && m_enclosing->contains(name)) {
        m_enclosing->set(name, value);
    }
}

void Scope::create(const std::string &name, Variable variable) {
    if (m_variables.count(name) > 0) m_variables[name] = variable;
    else m_variables.insert(std::make_pair(name, variable));
}