#include "h/Allocator.h"

Object *Allocator::m_previous = nullptr;
Object *Allocator::m_first = nullptr;
int Allocator::m_bytesAllocated = 0;

StringObject* Allocator::makeStringObject(std::string value) {
    StringObject *object = new StringObject{std::move(value)};

    setNext(object);
    m_bytesAllocated += sizeof(StringObject);

    return object;
}

IdentifierObject* Allocator::makeIdentifierObject(std::string value) {
    IdentifierObject *object = new IdentifierObject{std::move(value)};

    setNext(object);
    m_bytesAllocated += sizeof(IdentifierObject);

    return object;
}

void Allocator::setNext(Object *object) {
    if (m_previous) {
        m_previous->next = object;
        m_previous = object;
    } else {
        m_first = object;
        m_previous = object;
        m_previous->next = nullptr;
    }
}

Object *Allocator::objects() {
    return m_first;
}
