#ifndef MATILDA_VALUE_H
#define MATILDA_VALUE_H

#include <iostream>

class Value {
public:
    enum class Type {
        BOOL,
        NIL,
        NUMBER
    };
private:
    Type m_type;
    union {
        bool boolean;
        double number;
    } m_as;
public:
    Value();
    explicit Value(bool boolean);
    explicit Value(double number);

    bool operator==(Value value);

    bool isBool() const;
    bool isNil() const;
    bool isNumber() const;

    bool asBool() const;
    double asNumber() const;

    bool isFalsey() const;
    bool isTruthy() const;
};

inline std::ostream& operator<<(std::ostream &stream, const Value &value) {
    if (value.isBool()) stream << (value.asBool() ? "true" : "false");
    else if (value.isNil()) stream << "nil";
    else if (value.isNumber()) stream << value.asNumber();

    return stream;
}

#endif //MATILDA_VALUE_H
