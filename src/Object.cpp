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

bool Object::isIdentifier() const {
    return m_type == ObjectType::IDENTIFIER;
}

std::ostream& operator<<(std::ostream &stream, Object &object) {
    if (object.isString()) stream << object.asString()->asStdString();
    return stream;
}

StringObject* Object::asString() {
    return ((StringObject*)this);
}

IdentifierObject* Object::asIdentifier() {
    return ((IdentifierObject*)this);
}

StringObject::StringObject(std::string value) : Object{ObjectType::STRING}, m_str{std::move(value)} {}

StringObject StringObject::operator+(StringObject &object) const {
    return StringObject{m_str + object.m_str};
}

const std::string& StringObject::asStdString() const {
    return m_str;
}

IdentifierObject::IdentifierObject(std::string value) : Object{ObjectType::IDENTIFIER}, m_str{std::move(value)} {}

const std::string &IdentifierObject::asStdString() const {
    return m_str;
}

Object *Allocator::m_last = nullptr;

StringObject* Allocator::makeStringObject(std::string value) {
    StringObject *object = new StringObject{std::move(value)};
    setNext(object);

    return object;
}

IdentifierObject* Allocator::makeIdentifierObject(std::string value) {
    IdentifierObject *object = new IdentifierObject{std::move(value)};
    setNext(object);
    return object;
}

void Allocator::setNext(Object *object) {
    if (m_last) {
        m_last->next = object;
        m_last = object;
    } else {
        m_last = object;
        m_last->next = nullptr;
    }
}
