#ifndef ENACT_STMT_H
#define ENACT_STMT_H

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

    virtual std::string accept(Stmt::Visitor<std::string> *visitor) = 0;
    virtual void accept(Stmt::Visitor<void> *visitor) = 0;
};

class Stmt::Expression : public Stmt {
public:
    Sp<Expr> expr;

    Expression(Sp<Expr> expr) : expr{expr} {}

    inline std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitExpressionStmt(*this);
    }

    inline void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitExpressionStmt(*this);
    }
};

class Stmt::Print : public Stmt {
public:
    Sp<Expr> expr;

    Print(Sp<Expr> expr) : expr{expr} {}

    inline std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitPrintStmt(*this);
    }

    inline void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitPrintStmt(*this);
    }
};

class Stmt::Variable : public Stmt {
public:
    Token name;
    Sp<Expr> initializer;
    bool isConst;

    Variable(Token name, Sp<Expr> initializer, bool isConst) : name{std::move(name)}, initializer{initializer}, isConst{isConst} {}

    inline std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitVariableStmt(*this);
    }

    inline void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitVariableStmt(*this);
    }
};

#endif //ENACT_STMT_H
