#include "h/Environment.h"

Environment::Environment(Environment *enclosing) : m_enclosing{enclosing} {}

Value Environment::find(const std::string &name) {
    return m_variables[name];
}

bool Environment::contains(const std::string &name) {
    if (m_variables.count(name) > 0) {
        return true;
    }

    if (m_enclosing) return m_enclosing->contains(name);
    return false;
}

void Environment::set(const std::string &name, Value value) {
    if (m_variables.count(name) > 0) {
        m_variables[name] = value;
    }

    if (m_enclosing && m_enclosing->contains(name)) {
        m_enclosing->set(name, value);
    }
}

void Environment::create(const std::string &name, Value value) {
    m_variables.insert(std::make_pair(name, value));
}