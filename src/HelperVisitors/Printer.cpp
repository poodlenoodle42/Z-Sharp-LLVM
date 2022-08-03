#include "Printer.hpp"
#include "AST.hpp"
#include <iostream>
#include <sstream>
namespace Visitor {
    void Printer::printIndent() {
        for(int i = 0; i<indentation; i++) {
            std::cout << "  |  ";
        }
    }

    void Printer::visitBloc(AST::BlockStmt& stmt) {
        indentation++;

        std::cout << "Block\n";
        for (const auto& st : stmt.getStmts()) {
            printIndent();
            std::cout << "  |-> ";
            st->accept(*this);
        }
        

        indentation--;
    }

    void Printer::visitFunction(AST::Function& func) {
        indentation++;

        std::cout << "Function " << func.getName() << "(";
        std::stringstream arguments;
        for (const auto& arg : func.getArguments()) {
            arguments << arg << ",";
        }
        auto argumentsStr = arguments.str();
        argumentsStr.pop_back();
        std::cout << argumentsStr << ")\n";
        printIndent();
        std::cout << "  |-> ";
        func.body->accept(*this);
        indentation--;
    }

    void Printer::visitExprStmt(AST::ExprStmt& stmt) {

    }

}