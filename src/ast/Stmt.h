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
};

class Stmt::Expression : public Stmt {
public:
    std::shared_ptr<Expr> expr;

    Expression(std::shared_ptr<Expr> expr) : expr{expr} {}

    template <typename R>
    inline R accept(Stmt::Visitor<R> visitor) {
        return visitor.visitExpressionStmt(this);
    }
};

class Stmt::Print : public Stmt {
public:
    std::shared_ptr<Expr> expr;

    Print(std::shared_ptr<Expr> expr) : expr{expr} {}

    template <typename R>
    inline R accept(Stmt::Visitor<R> visitor) {
        return visitor.visitPrintStmt(this);
    }
};

class Stmt::Variable : public Stmt {
public:
    Token name;
    std::shared_ptr<Expr> initializer;
    bool isConst;

    Variable(Token name, std::shared_ptr<Expr> initializer, bool isConst) : name{std::move(name)}, initializer{initializer}, isConst{isConst} {}

    template <typename R>
    inline R accept(Stmt::Visitor<R> visitor) {
        return visitor.visitVariableStmt(this);
    }
};

#endif //ENACT_STMT_H
