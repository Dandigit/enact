#include "h/Value.h"

Value::Value() : m_type{Type::NIL}, m_as{.number = 0.0} {}
Value::Value(bool boolean) : m_type{Type::BOOL}, m_as{.boolean = boolean} {}
Value::Value(double number) : m_type{Type::NUMBER}, m_as{.number = number} {}

bool Value::operator==(Value value) {
    if (value.m_type != this->m_type) return false;
    switch (this->m_type) {
        case Type::BOOL: return this->asBool() == value.asBool();
        case Type::NIL: return true;
        case Type::NUMBER: return this->asNumber() == value.asNumber();
    }
}

bool Value::isBool() const {
    return m_type == Type::BOOL;
}

bool Value::isNil() const {
    return m_type == Type::NIL;
}

bool Value::isNumber() const {
    return m_type == Type::NUMBER;
}

bool Value::asBool() const {
    return m_as.boolean;
}

double Value::asNumber() const {
    return m_as.number;
}