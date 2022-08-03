#pragma once

#include "Expression.hpp"
#include "Statement.hpp"
#include <string>
#include "location.hh"
namespace AST {


    class Function {
        std::vector<std::string> argumentNames;
        std::string functionName;
        public:
            std::unique_ptr<BlockStmt> body;
            Function(std::string&& functionName, const std::vector<std::string>& argumentNames, std::unique_ptr<BlockStmt> body)
                : functionName(std::move(functionName)), argumentNames(std::move(argumentNames)), body(std::move(body)) {}
            void accept(Visitor& vis) {vis.visitFunction(*this);}
            const std::vector<std::string>& getArguments() const {return argumentNames;}
            const std::string& getName() const {return functionName;}
    };


    class AST {
        private:
            std::vector<std::unique_ptr<Function>> functions;
        public:
            void addFunction(std::unique_ptr<Function> func) {functions.push_back(std::move(func));}
            void accept(Visitor& vis) {
                for (auto& func : functions) {
                    func->accept(vis);
                }
            }
    };
};

