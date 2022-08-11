#pragma once
#include "Visitor.hpp"
#include "location.hh"
#include "Expression.hpp"
#include <vector>
#include <string>
#include <memory>
#include <optional>

namespace AST {
    class Statement {
        yy::location location;
        public:
            Statement(yy::location loc) : location(loc) {}
            Statement() {}
            inline yy::location getLocation() const {return location;}
            virtual ~Statement() {}
            virtual void accept(Visitor& vis) = 0;
    };

    typedef std::unique_ptr<Statement> StmtPtr;

    class BlockStmt : public Statement {
        std::vector<StmtPtr> stmts;
        public:
            BlockStmt(yy::location loc, std::vector<StmtPtr>&& stmts) : Statement(loc), stmts(std::move(stmts)) {}
            void accept(Visitor& vis) override {vis.visitBloc(*this);}
            const std::vector<StmtPtr>& getStmts() const {return stmts;}
    };


    class ExprStmt : public Statement {
        public:
            ExprPtr expr;
            ExprStmt(yy::location loc, ExprPtr expr) : Statement(loc), expr(std::move(expr)) {}
            void accept(Visitor& vis) override {vis.visitExprStmt(*this);}
    };

    class IfStmt : public Statement {
        public:
            ExprPtr expression;
            StmtPtr ifStmt;
            std::optional<StmtPtr> elseStmt;
            IfStmt(yy::location loc, ExprPtr expr, StmtPtr ifStmt, StmtPtr elseStmt) 
                : Statement(loc), expression(std::move(expr)), ifStmt(std::move(ifStmt)), elseStmt(std::move(elseStmt)) {}
            IfStmt(yy::location loc, ExprPtr expr, StmtPtr ifStmt)
                : Statement(loc), expression(std::move(expr)), ifStmt(std::move(ifStmt)), elseStmt() {}

            void accept(Visitor& vis) override {vis.visitIfStmt(*this);}
            
    };
};
