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
};

class Stmt::Expression : public Stmt {
public:
    Expr expr;

    Expression(Expr expr) : expr{expr} {}

    template <typename R>
    inline R accept(Stmt::Visitor<R> visitor) {
        return visitor.visitExpressionStmt(this);
    }
};

class Stmt::Print : public Stmt {
public:
    Expr expr;

    Print(Expr expr) : expr{expr} {}

    template <typename R>
    inline R accept(Stmt::Visitor<R> visitor) {
        return visitor.visitPrintStmt(this);
    }
};

class Stmt::Variable : public Stmt {
public:
    Token name;
    Expr initializer;

    Variable(Token name, Expr initializer) : name{name}, initializer{initializer} {}

    template <typename R>
    inline R accept(Stmt::Visitor<R> visitor) {
        return visitor.visitVariableStmt(this);
    }
};

#endif //MATILDA_STMT_H