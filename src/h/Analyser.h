#ifndef ENACT_ANALYSER_H
#define ENACT_ANALYSER_H

#include "../ast/Expr.h"
#include "../ast/Stmt.h"

class Analyser : private Expr::Visitor<void>, private Stmt::Visitor<void> {
    void visitExpressionStmt(Stmt::Expression stmt) override;
    void visitPrintStmt(Stmt::Print stmt) override;
    void visitVariableStmt(Stmt::Variable stmt) override;

    void visitAssignExpr(Expr::Assign expr) override;
    void visitBinaryExpr(Expr::Binary expr) override;
    void visitCallExpr(Expr::Call expr) override;
    void visitLiteralExpr(Expr::Literal expr) override;
    void visitTernaryExpr(Expr::Ternary expr) override;
    void visitUnaryExpr(Expr::Unary expr) override;
    void visitVariableExpr(Expr::Variable expr) override;
public:
    void analyse(std::vector<std::shared_ptr<Stmt>> statements);
};

#endif //ENACT_ANALYSER_H
