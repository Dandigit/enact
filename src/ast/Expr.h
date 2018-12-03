#ifndef ENACT_EXPR_H
#define ENACT_EXPR_H

#include "../h/Token.h"
#include "../h/Value.h"

#include <memory>

class Expr {
public:
    class Assign;
    class Binary;
    class Call;
    class Literal;
    class Ternary;
    class Unary;
    class Variable;

    template <class R>
    class Visitor {
    public:
        virtual R visitAssignExpr(Assign expr);
        virtual R visitBinaryExpr(Binary expr);
        virtual R visitCallExpr(Call expr);
        virtual R visitLiteralExpr(Literal expr);
        virtual R visitTernaryExpr(Ternary expr);
        virtual R visitUnaryExpr(Unary expr);
        virtual R visitVariableExpr(Variable expr);
    };
};

class Expr::Assign : public Expr {
public:
    std::shared_ptr<Expr> left, right;
    Token oper;

    Assign(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right, Token oper) : left{left}, right{right}, oper{std::move(oper)} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitAssignExpr(this);
    }
};

class Expr::Binary : public Expr {
public:
    std::shared_ptr<Expr> left, right;
    Token oper;

    Binary(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right, Token oper) : left{left}, right{right}, oper{std::move(oper)} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitBinaryExpr(this);
    }
};

class Expr::Call : public Expr {
public:
    std::shared_ptr<Expr> callee;
    std::vector<std::shared_ptr<Expr>> arguments;
    Token paren;

    Call(std::shared_ptr<Expr> callee, std::vector<std::shared_ptr<Expr>> arguments, Token paren) : callee{callee}, arguments{std::move(arguments)}, paren{std::move(paren)} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitCallExpr(this);
    }
};


class Expr::Literal : public Expr {
public:
    Value value;

    Literal(Value value) : value{value} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitLiteralExpr(this);
    }
};

class Expr::Ternary : public Expr {
public:
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Expr> thenExpr;
    std::shared_ptr<Expr> elseExpr;
    Token oper;

    Ternary(std::shared_ptr<Expr> condition, std::shared_ptr<Expr> thenExpr, std::shared_ptr<Expr> elseExpr, Token oper) : condition{condition}, thenExpr{thenExpr}, elseExpr{elseExpr}, oper{std::move(oper)} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitTernaryExpr(this);
    }
};

class Expr::Unary : public Expr {
public:
    std::shared_ptr<Expr> operand;
    Token oper;

    Unary(std::shared_ptr<Expr> operand, Token oper) : operand{operand}, oper{std::move(oper)} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitUnaryExpr(this);
    }
};

class Expr::Variable : public Expr {
public:
    Token name;

    explicit Variable(Token name) : name{std::move(name)} {}

    template <typename R>
    inline R accept(Expr::Visitor<R> visitor) {
        return visitor.visitVariableExpr(this);
    }
};

#endif //ENACT_EXPR_H
