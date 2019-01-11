# This script generates the AST classes found in Expr.h/cpp and Stmt.h/cpp.

uncapitalize = lambda s: s[:1].lower() + s[1:] if s else ''

def generate_ast_class_visitors(name, type_fields, visitor_types):
    ret = "    template <class R>\n    class Visitor {\n    public:\n"
    for key in type_fields:
        ret += f"        virtual R visit{key+name}({key} {uncapitalize(name)});\n"
    ret += "    };\n\n"
    for type in visitor_types:
        ret += f"    virtual {type} accept({name}::Visitor<{type}> *visitor) = 0;\n"
    return ret

def generate_ast_subclasses(name, type_fields, vistor_types):
    ret = ""
    for key in type_fields:
        ret += f"class {name}::{key} : public {name} {{\npublic:\n"
        if len(type_fields[key]) > 0:
            for field in type_fields[key]:
                ret += "    " + field + ";\n"
            ret += f"\n    {key}("
            for field in type_fields[key]:
                ret += field + ","
            ret = ret[:len(ret)-1]
            ret += ") : \n        "
            for field in type_fields[key]:
                ret += f"{field.split(' ')[1]}{{{field.split(' ')[1]}}},"
            ret = ret[:len(ret)-1]
            ret += " {}\n"
        else:
            ret += f"    {key}() {{}}\n"
        for visitor_type in vistor_types:
            ret += f"\n    {visitor_type} accept({name}::Visitor<{visitor_type}> *visitor) override {{\n        return visitor->visit{key+name}(*this);\n    }}\n"
        ret += "};\n\n"
    return ret

def generate_ast_class_body(name, type_fields, visitor_types):
    ret = ""
    for key in type_fields:
        ret += f"    class {key};\n"
    ret += "\n" + generate_ast_class_visitors(name, type_fields, visitor_types)
    ret += "};\n\n"
    return ret

def generate_includes(includes):
    ret = ""
    for include in includes:
        ret += f"#include {include}\n"
    return ret

def generate_ast_class(name, type_fields, visitor_types, includes):
    ret = ("// This file was automatically generated.\n"
           "// \"See generate.py\" for details.\n\n"
           f"#ifndef ENACT_{name.upper()}_H\n"
           f"#define ENACT_{name.upper()}_H\n\n"

           f"{generate_includes(includes)}\n"
           
           f"class {name} {{\n"
           "public:\n"
           f"{generate_ast_class_body(name, type_fields, visitor_types)}"
           f"{generate_ast_subclasses(name, type_fields, visitor_types)}"
           f"#endif // ENACT_{name.upper()}_H\n"
           )
    return ret

def generate_tree(name, type_fields, visitor_types, includes):
    with open(name + ".h", "w") as file:
        file.write(generate_ast_class(name, type_fields, visitor_types, includes))

generate_tree(
    "Expr",
    {
        "Assign"    : ["std::shared_ptr<Expr> left", "std::shared_ptr<Expr> right", "Token oper"],
        "Binary"    : ["std::shared_ptr<Expr> left", "std::shared_ptr<Expr> right", "Token oper"],
        "Boolean"   : ["bool value"],
        "Call"      : ["std::shared_ptr<Expr> callee", "std::vector<std::shared_ptr<Expr>> arguments", "Token paren"],
        "Logical"   : ["std::shared_ptr<Expr> left", "std::shared_ptr<Expr> right", "Token oper"],
        "Nil"       : [],
        "Number"    : ["double value"],
        "String"    : ["std::string value"],
        "Ternary"   : ["std::shared_ptr<Expr> condition", "std::shared_ptr<Expr> thenExpr", "std::shared_ptr<Expr> elseExpr", "Token oper"],
        "Unary"     : ["std::shared_ptr<Expr> operand", "Token oper"],
        "Variable"  : ["Token name"]
    },
    ["std::string", "void"],
    ['"../h/Token.h"', "<memory>", "<vector>"]
)

generate_tree(
    "Stmt",
    {
        "Expression" : ["std::shared_ptr<Expr> expr"],
        "Variable" : ["Token name", "std::shared_ptr<Expr> initializer", "bool isConst"],
    },
    ["std::string", "void"],
    ['"Expr.h"']
)