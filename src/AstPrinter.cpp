#include "h/AstPrinter.h"

std::string AstPrinter::print(std::shared_ptr<Stmt> stmt) {
    return stmt->accept(this);
}

std::string AstPrinter::visitExpressionStmt(Stmt::Expression stmt) {
    return "expression stmt";
}

std::string AstPrinter::visitPrintStmt(Stmt::Print stmt) {
    return "print stmt";
}

std::string AstPrinter::visitVariableStmt(Stmt::Variable stmt) {
    return "var stmt";
}

std::string AstPrinter::visitAssignExpr(Expr::Assign expr) {
    return "";
}

std::string AstPrinter::visitBinaryExpr(Expr::Binary expr) {
    return "";
}

std::string AstPrinter::visitLiteralExpr(Expr::Literal expr) {
    return "";
}

std::string AstPrinter::visitUnaryExpr(Expr::Unary expr) {
    return "";
}

std::string AstPrinter::visitVariableExpr(Expr::Variable expr) {
    return "";
}

