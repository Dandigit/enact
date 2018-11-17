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

    friend std::ostream& operator << (std::ostream &stream, Value value) {
        if (value.isBool()) std::cout << (value.asBool() ? "true" : "false");
        else if (value.isNil()) std::cout << "nil";
        else if (value.isNumber()) std::cout << value.asNumber();

        return stream;
    }

    bool isBool() const;
    bool isNil() const;
    bool isNumber() const;

    bool asBool() const;
    double asNumber() const;

    bool isFalsey() const;
    bool isTruthy() const;
};

#endif //MATILDA_VALUE_H
