//
// Created by dan on 21/10/18.
//

#ifndef MATILDA_OBJECT_H
#define MATILDA_OBJECT_H

#include <string>

using std::string;

class Object {
protected:

    void *value;

public:

    template <class Type>
    void operator=(Type value);

    template <>
    void operator=<string>(string value);

    template <class Type>
    void operator==(Type compared);

    template <>
    bool operator==<Object>(Object compared);

    template <class ReturnType>
    ReturnType get();

    template <>
    string get();

    template <>
    void* get();
};


#endif //MATILDA_OBJECT_H
