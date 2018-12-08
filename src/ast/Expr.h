#ifndef ENACT_EXPR_H
#define ENACT_EXPR_H

#include "../h/Token.h"
#include "../h/Value.h"

#include <memory>
#include <vector>

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

    virtual std::string accept(Expr::Visitor<std::string> *visitor) = 0;
    virtual void accept(Expr::Visitor<void> *visitor) = 0;
};

class Expr::Assign : public Expr {
public:
    Sp<Expr> left, right;
    Token oper;

    Assign(Sp<Expr> left, Sp<Expr> right, Token oper) : left{left}, right{right}, oper{std::move(oper)} {}

    inline std::string accept(Expr::Visitor<std::string> *visitor) override {
        return visitor->visitAssignExpr(*this);
    }

    inline void accept(Expr::Visitor<void> *visitor) override {
        return visitor->visitAssignExpr(*this);
    }
};

class Expr::Binary : public Expr {
public:
    Sp<Expr> left, right;
    Token oper;

    Binary(Sp<Expr> left, Sp<Expr> right, Token oper) : left{left}, right{right}, oper{std::move(oper)} {}

    inline std::string accept(Expr::Visitor<std::string> *visitor) override {
        return visitor->visitBinaryExpr(*this);
    }

    inline void accept(Expr::Visitor<void> *visitor) override {
        return visitor->visitBinaryExpr(*this);
    }
};

class Expr::Call : public Expr {
public:
    Sp<Expr> callee;
    std::vector<Sp<Expr>> arguments;
    Token paren;

    Call(Sp<Expr> callee, std::vector<Sp<Expr>> arguments, Token paren) : callee{callee}, arguments{std::move(arguments)}, paren{std::move(paren)} {}

    inline std::string accept(Expr::Visitor<std::string> *visitor) override {
        return visitor->visitCallExpr(*this);
    }

    inline void accept(Expr::Visitor<void> *visitor) override {
        return visitor->visitCallExpr(*this);
    }
};


class Expr::Literal : public Expr {
public:
    Value value;

    Literal(Value value) : value{value} {}

    inline std::string accept(Expr::Visitor<std::string> *visitor) override {
        return visitor->visitLiteralExpr(*this);
    }

    inline void accept(Expr::Visitor<void> *visitor) override {
        return visitor->visitLiteralExpr(*this);
    }
};

class Expr::Ternary : public Expr {
public:
    Sp<Expr> condition;
    Sp<Expr> thenExpr;
    Sp<Expr> elseExpr;
    Token oper;

    Ternary(Sp<Expr> condition, Sp<Expr> thenExpr, Sp<Expr> elseExpr, Token oper) : condition{condition}, thenExpr{thenExpr}, elseExpr{elseExpr}, oper{std::move(oper)} {}

    inline std::string accept(Expr::Visitor<std::string> *visitor) override {
        return visitor->visitTernaryExpr(*this);
    }

    inline void accept(Expr::Visitor<void> *visitor) override {
        return visitor->visitTernaryExpr(*this);
    }
};

class Expr::Unary : public Expr {
public:
    Sp<Expr> operand;
    Token oper;

    Unary(Sp<Expr> operand, Token oper) : operand{operand}, oper{std::move(oper)} {}

    inline std::string accept(Expr::Visitor<std::string> *visitor) override {
        return visitor->visitUnaryExpr(*this);
    }

    inline void accept(Expr::Visitor<void> *visitor) override {
        return visitor->visitUnaryExpr(*this);
    }
};

class Expr::Variable : public Expr {
public:
    Token name;

    explicit Variable(Token name) : name{std::move(name)} {}

    inline std::string accept(Expr::Visitor<std::string> *visitor) override {
        return visitor->visitVariableExpr(*this);
    }

    inline void accept(Expr::Visitor<void> *visitor) override {
        return visitor->visitVariableExpr(*this);
    }
};

#endif //ENACT_EXPR_H
