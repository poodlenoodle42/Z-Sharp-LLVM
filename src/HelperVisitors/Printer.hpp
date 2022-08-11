#pragma once
#include "Visitor.hpp"
namespace Visitor {
    class Printer : public AST::Visitor {
        int indentation = -1;
        void printIndent();
        public:
            void visitFunction(AST::Function& func) override;
            void visitBloc(AST::BlockStmt& stmt) override;
            void visitExprStmt(AST::ExprStmt& stmt) override;
            void visitIfStmt(AST::IfStmt& stmt) override;

            void visitBinary(AST::BinaryExpr& expr) override;
            void visitUnary(AST::UnaryExpr& expr) override;
            void visitNumberLiteral(AST::NumberLiteral& expr) override;
            void visitStringLiteral(AST::StringLiteral& expr) override;
            void visitBoolLiteral(AST::BoolLiteral& expr) override;
            void visitIdentifier(AST::Identifier& expr) override;
            void visitCallExpr(AST::CallExpr& expr) override;
    };

};