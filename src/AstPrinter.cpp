#include <sstream>
#include "h/AstPrinter.h"

void AstPrinter::print(Sp<Stmt> stmt) {
    std::cout << stmt->accept(this);
}

std::string AstPrinter::evaluate(Sp<Expr> expr) {
    return expr->accept(this);
}

std::string AstPrinter::visitExpressionStmt(Stmt::Expression stmt) {
    return "Stmt:Expression " + evaluate(stmt.expr);
}

std::string AstPrinter::visitPrintStmt(Stmt::Print stmt) {
    return "Stmt:Print " + evaluate(stmt.expr);
}

std::string AstPrinter::visitVariableStmt(Stmt::Variable stmt) {
    return "Stmt:Var " + stmt.name.lexeme + " " + evaluate(stmt.initializer);
}

std::string AstPrinter::visitAssignExpr(Expr::Assign expr) {
    return "(= " + evaluate(expr.left) + " " + evaluate(expr.right) + ")";
}

std::string AstPrinter::visitBinaryExpr(Expr::Binary expr) {
    return "(" + expr.oper.lexeme + " " + evaluate(expr.left) + " " + evaluate(expr.right) + ")";
}

std::string AstPrinter::visitCallExpr(Expr::Call expr) {
    return "(() " + evaluate(expr.callee) + ")";
}

std::string AstPrinter::visitLiteralExpr(Expr::Literal expr) {
    std::stringstream s;
    s << expr.value;
    return s.str();
}

std::string AstPrinter::visitTernaryExpr(Expr::Ternary expr) {
    return "(?: " + evaluate(expr.condition) + " " + evaluate(expr.thenExpr) + " " + evaluate(expr.elseExpr) + ")";
}

std::string AstPrinter::visitUnaryExpr(Expr::Unary expr) {
    return "(" + expr.oper.lexeme + " " + evaluate(expr.operand) + ")";
}

std::string AstPrinter::visitVariableExpr(Expr::Variable expr) {
    return "(var " + expr.name.lexeme + ")";
}

