#pragma once
#include "Visitor.hpp"
namespace Visitor {
    class Printer : public AST::Visitor {
        int indentation = -1;
        void printIndent();
        public:
            void visitFunction(AST::Function& func);
            void visitBloc(AST::BlockStmt& stmt);
            void visitExprStmt(AST::ExprStmt& stmt);
    };

};