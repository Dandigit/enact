#ifndef MATILDA_OBJECT_H
#define MATILDA_OBJECT_H

#include <string>

enum class ObjectType {
    STRING
};

class StringObject;

class Object {
private:
    ObjectType type;
    Object *next;
public:
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

    StringObject operator+(const StringObject &object) const;
    const std::string& asStdString() const;
};

#endif //MATILDA_OBJECT_H
