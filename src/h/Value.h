#ifndef MATILDA_VALUE_H
#define MATILDA_VALUE_H

#include <iostream>

#include "Object.h"

class Value {
public:
    enum class Type {
        BOOL,
        NIL,
        NUMBER,
        OBJECT,
    };
private:
    Type m_type;
    union {
        bool boolean;
        double number;
        Object *object;
    } m_as;
public:
    Value();
    explicit Value(bool boolean);
    explicit Value(double number);
    explicit Value(Object *object);

    bool operator==(Value value);

    bool isBool() const;
    bool isNil() const;
    bool isNumber() const;
    bool isObject() const;

    bool asBool() const;
    double asNumber() const;
    Object* asObject() const;

    bool isFalsey() const;
    bool isTruthy() const;
};

inline std::ostream& operator<<(std::ostream &stream, const Value &value) {
    if (value.isBool()) stream << (value.asBool() ? "true" : "false");
    else if (value.isNil()) stream << "nil";
    else if (value.isNumber()) stream << value.asNumber();
    else if (value.isObject()) stream << *value.asObject();

    return stream;
}

#endif //MATILDA_VALUE_H
