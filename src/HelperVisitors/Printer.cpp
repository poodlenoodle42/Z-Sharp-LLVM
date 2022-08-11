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
        if (func.getArguments().size() > 0) {
            std::stringstream arguments;
            for (const auto& arg : func.getArguments()) {
                arguments << arg << ",";
            }
            auto argumentsStr = arguments.str();
            argumentsStr.pop_back();
            std::cout << argumentsStr << ")\n";
        } else {
            std::cout << ")\n";
        }
        printIndent();
        std::cout << "  |-> ";
        func.body->accept(*this);
        indentation--;
    }

    void Printer::visitExprStmt(AST::ExprStmt& stmt) {
        stmt.expr->accept(*this);
    }

    void Printer::visitIfStmt(AST::IfStmt& stmt) {
        indentation++;
        std::cout << "If\n";
        printIndent();
        std::cout << "  |-> ";
        stmt.expression->accept(*this);
        printIndent();
        std::cout << "then> ";
        stmt.ifStmt->accept(*this);
        if (stmt.elseStmt) {
            printIndent();
            std::cout << "else> ";
            (*stmt.elseStmt)->accept(*this);
        } 


        indentation--;
    }

    void Printer::visitBinary(AST::BinaryExpr& expr) {
        indentation++;
        std::cout << "Binary ";
        switch (expr.getType()) {
            case AST::BinaryExpr::Type::PLUS: std::cout << "+"; break;
            case AST::BinaryExpr::Type::MINUS: std::cout << "-"; break;
            case AST::BinaryExpr::Type::MULT: std::cout << "*"; break;
            case AST::BinaryExpr::Type::DIV: std::cout << "/"; break;
            case AST::BinaryExpr::Type::EQUALSEQUALS: std::cout << "=="; break;
            case AST::BinaryExpr::Type::GREATER: std::cout << ">"; break;
            case AST::BinaryExpr::Type::LESS: std::cout << "<"; break;
            case AST::BinaryExpr::Type::GREATER_EQUALS: std::cout << ">="; break;
            case AST::BinaryExpr::Type::LESS_EQUALS: std::cout << "<="; break;
        }
        std::cout << "\n";
        printIndent();
        std::cout << "  |-> ";
        expr.left->accept(*this);
        printIndent();
        std::cout << "  |-> ";
        expr.right->accept(*this);
        //std::cout << "\n";
        indentation--;
        //printIndent();
    }


    void Printer::visitUnary(AST::UnaryExpr& expr) {
        indentation++;
        std::cout << "Unary ";
        switch (expr.getType()) {
            case AST::UnaryExpr::Type::NEGATE: std::cout << "-"; break;
            case AST::UnaryExpr::Type::NOT: std::cout << "!"; break;
        }
        std::cout << "\n";
        printIndent();
        std::cout << "  |-> ";
        expr.expr->accept(*this);
        indentation--;
    }

    void Printer::visitNumberLiteral(AST::NumberLiteral& expr) {
        switch (expr.getType()) {
            case AST::NumberLiteral::Type::DOUBLE: std::cout << expr.getDouble(); break;
            case AST::NumberLiteral::Type::INTEGER: std::cout << expr.getInt(); break;
        }
        std::cout << "\n";
    }

    void Printer::visitStringLiteral(AST::StringLiteral& expr) {
        std::cout << "String: " << expr.getString() << "\n";
    }

    void Printer::visitBoolLiteral(AST::BoolLiteral& expr) {
        std::cout << "Bool: " << (expr.getValue() ? "true" : "false") << "\n";
    }

    void Printer::visitIdentifier(AST::Identifier& expr) {
        std::cout << "Identifier: " << expr.getString() << "\n";
    }

    void Printer::visitCallExpr(AST::CallExpr& expr) {
        indentation++;
        std::cout << "Call " << expr.getCallee() << "\n";
        for(const auto& arg : expr.arguments) {
            printIndent();
            std::cout << "  |-> ";
            arg->accept(*this);
        }
        indentation--;
    }
}