#ifndef MATILDA_EXPR_H
#define MATILDA_EXPR_H

#include "../h/Token.h"
#include "../h/Value.h"

class Expr {
public:
    class Assign;
    class Binary;
    class Literal;
    class Unary;
    class Variable;

    template <class R>
    class Visitor {
    public:
        virtual R visitAssignExpr(Assign expr);
        virtual R visitBinaryExpr(Binary expr);
        virtual R visitLiteralExpr(Literal expr);
        virtual R visitUnaryExpr(Unary expr);
        virtual R visitVariableExpr(Variable expr);
    };
};

class Expr::Assign : public Expr {
public:
    Expr left, right;
    Token oper;

    Assign(Expr left, Expr right, Token oper) : left{left}, right{right}, oper{std::move(oper)} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitAssignExpr(this);
    }
};

class Expr::Binary : public Expr {
public:
    Value left, right;
    Token oper;

    Binary(Value left, Value right, Token oper) : left{left}, right{right}, oper{oper} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitBinaryExpr(this);
    }
};

class Expr::Literal : public Expr {
public:
    Expr value;

    Literal(Expr value) : value{value} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitLiteralExpr(this);
    }
};

class Expr::Unary : public Expr {
public:
    Expr value;
    Token oper;

    Unary(Expr value, Token oper) : value{value}, oper{oper} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitUnaryExpr(this);
    }
};

class Expr::Variable : public Expr {
public:
    Token name;

    Variable(Token name) : name{name} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitVariableExpr(this);
    }
};

#endif //MATILDA_EXPR_H
