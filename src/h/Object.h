#ifndef MATILDA_OBJECT_H
#define MATILDA_OBJECT_H

#include <iostream>
#include <string>

enum class ObjectType {
    STRING
};

class StringObject;

class Object {
private:
    ObjectType m_type;
public:
    explicit Object(ObjectType type);
    Object *next = nullptr;

    bool operator==(Object &object);

    bool isString() const;

    StringObject* asString();

    friend std::ostream& operator<<(std::ostream &stream, Object &object);
};

class StringObject : public Object {
private:
    std::string m_str;
public:
    explicit StringObject(std::string value);

    StringObject operator+(StringObject &object) const;
    const std::string& asStdString() const;
};

class Allocator {
private:
    static Object *m_last;
public:
    static StringObject* makeStringObject(std::string value);
};

#endif //MATILDA_OBJECT_H
