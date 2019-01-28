// This file was automatically generated.
// "See generate.py" for details.

#ifndef ENACT_STMT_H
#define ENACT_STMT_H

#include "Expr.h"
#include "trivialStructs.h"

class Stmt {
public:
    class Block;
    class Break;
    class Continue;
    class Each;
    class Expression;
    class For;
    class Function;
    class Given;
    class If;
    class Return;
    class Struct;
    class Trait;
    class While;
    class Variable;

    template <class R>
    class Visitor {
    public:
        virtual R visitBlockStmt(Block None) = 0;
        virtual R visitBreakStmt(Break None) = 0;
        virtual R visitContinueStmt(Continue None) = 0;
        virtual R visitEachStmt(Each None) = 0;
        virtual R visitExpressionStmt(Expression None) = 0;
        virtual R visitForStmt(For None) = 0;
        virtual R visitFunctionStmt(Function None) = 0;
        virtual R visitGivenStmt(Given None) = 0;
        virtual R visitIfStmt(If None) = 0;
        virtual R visitReturnStmt(Return None) = 0;
        virtual R visitStructStmt(Struct None) = 0;
        virtual R visitTraitStmt(Trait None) = 0;
        virtual R visitWhileStmt(While None) = 0;
        virtual R visitVariableStmt(Variable None) = 0;
    };

    virtual std::string accept(Stmt::Visitor<std::string> *visitor) = 0;
    virtual void accept(Stmt::Visitor<void> *visitor) = 0;
};

class Stmt::Block : public Stmt {
public:
    std::vector<std::shared_ptr<Stmt>> statements;

    Block(std::vector<std::shared_ptr<Stmt>> statements) : 
        statements{statements} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitBlockStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitBlockStmt(*this);
    }
};

class Stmt::Break : public Stmt {
public:
    Token keyword;

    Break(Token keyword) : 
        keyword{keyword} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitBreakStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitBreakStmt(*this);
    }
};

class Stmt::Continue : public Stmt {
public:
    Token keyword;

    Continue(Token keyword) : 
        keyword{keyword} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitContinueStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitContinueStmt(*this);
    }
};

class Stmt::Each : public Stmt {
public:
    Token name;
    std::shared_ptr<Expr> object;
    std::vector<std::shared_ptr<Stmt>> body;

    Each(Token name,std::shared_ptr<Expr> object,std::vector<std::shared_ptr<Stmt>> body) : 
        name{name},object{object},body{body} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitEachStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitEachStmt(*this);
    }
};

class Stmt::Expression : public Stmt {
public:
    std::shared_ptr<Expr> expr;

    Expression(std::shared_ptr<Expr> expr) : 
        expr{expr} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitExpressionStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitExpressionStmt(*this);
    }
};

class Stmt::For : public Stmt {
public:
    std::shared_ptr<Stmt> initializer;
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Expr> increment;
    std::vector<std::shared_ptr<Stmt>> body;

    For(std::shared_ptr<Stmt> initializer,std::shared_ptr<Expr> condition,std::shared_ptr<Expr> increment,std::vector<std::shared_ptr<Stmt>> body) : 
        initializer{initializer},condition{condition},increment{increment},body{body} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitForStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitForStmt(*this);
    }
};

class Stmt::Function : public Stmt {
public:
    Token name;
    std::string typeName;
    std::vector<Parameter> params;
    std::vector<std::shared_ptr<Stmt>> body;

    Function(Token name,std::string typeName,std::vector<Parameter> params,std::vector<std::shared_ptr<Stmt>> body) : 
        name{name},typeName{typeName},params{params},body{body} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitFunctionStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitFunctionStmt(*this);
    }
};

class Stmt::Given : public Stmt {
public:
    std::shared_ptr<Expr> value;
    std::vector<GivenCase> cases;

    Given(std::shared_ptr<Expr> value,std::vector<GivenCase> cases) : 
        value{value},cases{cases} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitGivenStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitGivenStmt(*this);
    }
};

class Stmt::If : public Stmt {
public:
    std::shared_ptr<Expr> condition;
    std::vector<std::shared_ptr<Stmt>> thenBlock;
    std::vector<std::shared_ptr<Stmt>> elseBlock;

    If(std::shared_ptr<Expr> condition,std::vector<std::shared_ptr<Stmt>> thenBlock,std::vector<std::shared_ptr<Stmt>> elseBlock) : 
        condition{condition},thenBlock{thenBlock},elseBlock{elseBlock} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitIfStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitIfStmt(*this);
    }
};

class Stmt::Return : public Stmt {
public:
    Token keyword;
    std::shared_ptr<Expr> value;

    Return(Token keyword,std::shared_ptr<Expr> value) : 
        keyword{keyword},value{value} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitReturnStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitReturnStmt(*this);
    }
};

class Stmt::Struct : public Stmt {
public:
    Token name;
    std::vector<Token> traits;
    std::vector<Field> fields;
    std::vector<std::shared_ptr<Stmt::Function>> methods;
    std::vector<std::shared_ptr<Stmt::Function>> assocFunctions;

    Struct(Token name,std::vector<Token> traits,std::vector<Field> fields,std::vector<std::shared_ptr<Stmt::Function>> methods,std::vector<std::shared_ptr<Stmt::Function>> assocFunctions) : 
        name{name},traits{traits},fields{fields},methods{methods},assocFunctions{assocFunctions} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitStructStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitStructStmt(*this);
    }
};

class Stmt::Trait : public Stmt {
public:
    Token name;
    std::vector<std::shared_ptr<Stmt::Function>> methods;

    Trait(Token name,std::vector<std::shared_ptr<Stmt::Function>> methods) : 
        name{name},methods{methods} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitTraitStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitTraitStmt(*this);
    }
};

class Stmt::While : public Stmt {
public:
    std::shared_ptr<Expr> condition;
    std::vector<std::shared_ptr<Stmt>> body;

    While(std::shared_ptr<Expr> condition,std::vector<std::shared_ptr<Stmt>> body) : 
        condition{condition},body{body} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitWhileStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitWhileStmt(*this);
    }
};

class Stmt::Variable : public Stmt {
public:
    Token name;
    std::string typeName;
    std::shared_ptr<Expr> initializer;
    bool isConst;

    Variable(Token name,std::string typeName,std::shared_ptr<Expr> initializer,bool isConst) : 
        name{name},typeName{typeName},initializer{initializer},isConst{isConst} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitVariableStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitVariableStmt(*this);
    }
};

#endif // ENACT_STMT_H
