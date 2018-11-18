#include "h/Object.h"

bool Object::operator==(Object &object) {
    if (this->type != object.type) return false;
    switch (this->type) {
        case ObjectType::STRING:
            return this->asString()->asStdString() == object.asString()->asStdString();
    }
}

bool Object::isString() const {
    return type == ObjectType::STRING;
}

std::ostream& operator<<(std::ostream &stream, Object &object) {
    if (object.isString()) stream << object.asString()->asStdString();
}

StringObject* Object::asString() {
    return ((StringObject*)this);
}

StringObject::StringObject(std::string value) : m_str{std::move(value)} {}

StringObject StringObject::operator+(const StringObject &object) const {
    return StringObject{m_str + object.m_str};
}

const std::string& StringObject::asStdString() const {
    return m_str;
}