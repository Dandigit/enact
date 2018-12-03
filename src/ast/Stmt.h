#ifndef MATILDA_STMT_H
#define MATILDA_STMT_H

#include "Expr.h"

class Stmt {
public:
    class Expression;
    class Print;
    class Variable;

    template <class R>
    class Visitor {
    public:
        virtual R visitExpressionStmt(Expression stmt);
        virtual R visitPrintStmt(Print stmt);
        virtual R visitVariableStmt(Variable stmt);
    };

    virtual std::string accept(Stmt::Visitor<std::string> *visitor);
};

class Stmt::Expression : public Stmt {
public:
    Expr expr;

    Expression(Expr expr) : expr{expr} {}

    inline std::string accept(Stmt::Visitor<std::string> *visitor) {
        return visitor->visitExpressionStmt(*this);
    }
};

class Stmt::Print : public Stmt {
public:
    Expr expr;

    Print(Expr expr) : expr{expr} {}

    inline std::string accept(Stmt::Visitor<std::string> *visitor) {
        return visitor->visitPrintStmt(*this);
    }
};

class Stmt::Variable : public Stmt {
public:
    Token name;
    Expr initializer;

    Variable(Token name, Expr initializer) : name{name}, initializer{initializer} {}

    inline std::string accept(Stmt::Visitor<std::string> *visitor) {
        return visitor->visitVariableStmt(*this);
    }
};

#endif //MATILDA_STMT_H
