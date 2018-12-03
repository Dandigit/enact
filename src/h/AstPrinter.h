#ifndef ENACT_ASTPRINTER_H
#define ENACT_ASTPRINTER_H

#include "../ast/Stmt.h"

#include <string>
#include <memory>

class AstPrinter : private Stmt::Visitor<std::string>, private Expr::Visitor<std::string> {
    std::string visitExpressionStmt(Stmt::Expression stmt) override;
    std::string visitPrintStmt(Stmt::Print stmt) override;
    std::string visitVariableStmt(Stmt::Variable stmt) override;

    std::string visitAssignExpr(Expr::Assign expr);
    std::string visitBinaryExpr(Expr::Binary expr);
    std::string visitCallExpr(Expr::Call expr);
    std::string visitLiteralExpr(Expr::Literal expr);
    std::string visitTernaryExpr(Expr::Ternary expr);
    std::string visitUnaryExpr(Expr::Unary expr);
    std::string visitVariableExpr(Expr::Variable expr);

    std::string evaluate(std::shared_ptr<Expr> expr);
public:
    void print(std::shared_ptr<Stmt> stmt);
};

#endif //ENACT_ASTPRINTER_H
