#include "h/Object.h"

Object::Object(ObjectType type) : m_type{type} {};

bool Object::operator==(Object &object) {
    if (this->m_type != object.m_type) return false;
    switch (this->m_type) {
        case ObjectType::STRING:
            return this->asString()->asStdString() == object.asString()->asStdString();
    }
}

bool Object::isString() const {
    return m_type == ObjectType::STRING;
}

std::ostream& operator<<(std::ostream &stream, Object &object) {
    if (object.isString()) stream << object.asString()->asStdString();
}

StringObject* Object::asString() {
    return ((StringObject*)this);
}

StringObject::StringObject(std::string value) : Object{ObjectType::STRING}, m_str{std::move(value)} {}

StringObject StringObject::operator+(StringObject &object) const {
    return StringObject{m_str + object.m_str};
}

const std::string& StringObject::asStdString() const {
    return m_str;
}