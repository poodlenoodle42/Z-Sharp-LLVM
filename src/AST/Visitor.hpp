#pragma once

namespace AST {
    class Function;
    class BlockStmt;
    class ExprStmt;

    class Visitor {
        public:
            virtual void visitFunction(Function& stmt) = 0;
            virtual void visitBloc(BlockStmt& stmt) = 0;
            virtual void visitExprStmt(ExprStmt& stmt) = 0;
    };
};
