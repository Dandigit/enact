#ifndef MATILDA_ALLOCATOR_H
#define MATILDA_ALLOCATOR_H

#include "Object.h"

class Allocator {
private:
    static Object *m_previous;
    static Object *m_first;
    static int m_bytesAllocated;
    static void setNext(Object *object);
public:
    static StringObject* makeStringObject(std::string value);
    static IdentifierObject* makeIdentifierObject(std::string value);

    static Object* objects();
};

#endif //MATILDA_ALLOCATOR_H
