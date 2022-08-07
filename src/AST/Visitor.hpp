#pragma once

namespace AST {
    class Function;
    class BlockStmt;
    class ExprStmt;

    class BinaryExpr;
    class UnaryExpr;
    class NumberLiteral;
    class Visitor {
        public:
            virtual void visitFunction(Function& stmt) = 0;
            virtual void visitBloc(BlockStmt& stmt) = 0;
            virtual void visitExprStmt(ExprStmt& stmt) = 0;

            virtual void visitBinary(BinaryExpr& expr) = 0;
            virtual void visitUnary(UnaryExpr& expr) = 0;
            virtual void visitNumberLiteral(NumberLiteral& expr) = 0;
    };
};
