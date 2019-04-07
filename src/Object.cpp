#include "h/Object.h"

Object::Object(ObjectType type) : m_type{type} {}

std::string Object::toString() const {
    if (is<StringObject>()) {
        return as<StringObject>()->asStdString();
    }

    return "";
}

std::ostream& operator<<(std::ostream& stream, const Object& object) {
    stream << object.toString();
    return stream;
}

StringObject::StringObject(std::string data) : Object{ObjectType::STRING}, m_data{std::move(data)} {

}

const std::string &StringObject::asStdString() const {
    return m_data;
}
