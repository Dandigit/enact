#ifndef ENACT_TYPE_H
#define ENACT_TYPE_H

#include "Token.h"
#include <vector>
#include <unordered_map>
#include <optional>

// Forward declarations from "../ast/Stmt.h":
class FunctionStmt;
struct NamedType;

// The type tree used to give expressions types.
// Here's what it looks like:

// Type
// ├── Numerical
// │   ├── Integral
// │   └── Decimal
// ├── String
// ├── Struct
// ├── Dynamic
// └── Nothing

class TypeBase;

// Type is just a managed pointer to TypeBase that allows for polymorphism.
typedef std::shared_ptr<TypeBase> Type;

enum class TypeKind {
    PRIMITIVE,
    ARRAY,
    FUNCTION,
    TRAIT,
    STRUCT,
    CONSTRUCTOR
};

class TypeBase {
private:
    TypeKind m_kind;
public:
    TypeBase(TypeKind kind);

    virtual TypeKind getKind() const;

    // Strict equality comparison - the types must be exactly the same
    virtual bool operator==(const TypeBase &type) const;
    virtual bool operator!=(const TypeBase &type) const;

    // Loose equality comparison - the types must be exactly the same,
    // dynamic, or convertible to each other.
    virtual bool looselyEquals(const TypeBase &type) const;

    virtual std::string toString() const;

    // Primitive type groups
    bool isNumeric() const;
    bool isInt() const;
    bool isFloat() const;
    bool isBool() const;
    bool isString() const;
    bool isDynamic() const;
    bool isNothing() const;

    bool maybeNumeric() const;
    bool maybeInt() const;
    bool maybeFloat() const;
    bool maybeBool() const;
    bool maybeString() const;

    // Complex type groups
    bool isArray() const;
    bool isFunction() const;
    bool isTrait() const;
    bool isStruct() const;
    bool isConstructor() const;

    bool maybeArray() const;
    bool maybeFunction() const;
    bool maybeTrait() const;
    bool maybeStruct() const;

    template<typename T>
    inline const T* as() const {
        return static_cast<const T*>(this);
    }
};

// Primitive types
// - numbers/strings/dynamic/nothing
enum class PrimitiveKind {
    INT,
    FLOAT,
    BOOL,
    STRING,
    DYNAMIC,
    NOTHING,
};

class PrimitiveType : public TypeBase {
private:
    PrimitiveKind m_kind;
public:
    PrimitiveType(PrimitiveKind kind);

    PrimitiveKind getPrimitiveKind() const;
};

// Array types
class ArrayType : public TypeBase {
    Type m_elementType;
public:
    ArrayType(Type elementType);

    const Type getElementType() const;
};

// Function types
class FunctionType : public TypeBase {
    Type m_returnType;
    std::vector<Type> m_argumentTypes;
public:
    FunctionType(Type returnType, std::vector<Type> argumentTypes);

    const Type getReturnType() const;
    const std::vector<Type>& getArgumentTypes() const;
};


// These two user-defined types (traits and structs) must store
// a pointer to their original declaration AST node.

// Trait types
class TraitType : public TypeBase {
    std::string m_name;
    std::unordered_map<std::string, Type> m_methods;
public:
    TraitType(std::string name, std::unordered_map<std::string, Type> methods);

    const std::string& getName() const;

    const std::unordered_map<std::string, Type>& getMethods() const;
    std::optional<Type> getMethod(const std::string& name) const;
};

// Struct types
class StructType : public TypeBase {
    std::string m_name;
    std::vector<Type> m_traits;

    std::unordered_map<std::string, Type> m_fields;
    std::unordered_map<std::string, Type> m_methods;
    std::unordered_map<std::string, Type> m_assocFunctions;
public:
    StructType(std::string name, std::vector<Type> traits, std::unordered_map<std::string, Type> fields,
               std::unordered_map<std::string, Type> methods, std::unordered_map<std::string, Type> assocFunctions);

    const std::string& getName() const;

    const std::vector<Type>& getTraits() const;
    const std::unordered_map<std::string, Type>& getFields() const;
    const std::unordered_map<std::string, Type>& getMethods() const;
    const std::unordered_map<std::string, Type>& getAssocFunctions() const;

    std::optional<Type> getTrait(const TypeBase& trait) const;

    std::optional<Type> getField(const std::string& name) const;
    std::optional<Type> getMethod(const std::string& name) const;
    std::optional<Type> getFieldOrMethod(const std::string& name) const;

    std::optional<Type> getAssocFunction(const std::string& name) const;
};

// Struct constructor types
class ConstructorType : public TypeBase {
    StructType m_structType;
    FunctionType m_functionType;
public:
    ConstructorType(StructType structType);

    const StructType& getStructType() const;
    const FunctionType& getFunctionType() const;
};

#endif //ENACT_TYPE_H