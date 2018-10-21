#include "../h/Object.h"

template <class Type>
void Object::operator=(Type value) {
    this->value = (void*)value;
}

template <>
void Object::operator=<string>(string value) {
    this->value = (void*)value.c_str();
}

template <class Type>
void Object::operator==(Type compared) {
    return (int)(void*)compared == (int)(void*)value;
}

template <>
bool Object::operator==<Object>(Object compared) {
    return compared.value == value;
}

template <class ReturnType>
ReturnType Object::get() {
    return (ReturnType)value;
}

template <>
string Object::get() {
    string str = (const char*)value;
    return str;
}

template <>
void* Object::get() {
    return value;
}