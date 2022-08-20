#pragma once
#include <vector>
#include <functional>
#include <map>
#include <utility>
#include <tuple>
#include "Expression.hpp"
#include <llvm/IR/Type.h>


namespace SymbolTable {
    class Type {
        public:
            enum class KindOfType {
                Primitive,
                Record,
                Void,
                Undecided
            };
            enum class BinaryOperators {
                PLUS,
                MINUS,
                MULT,
                DIV,
                EQUALS,
                GREATER,
                LESS,
                GREATER_EQUALS,
                LESS_EQUALS
            };
            enum class UnaryOperators {
                MINUS,
                NOT
            };
        private:
            KindOfType kind;
            llvm::Type* llvmType;
            std::map<std::pair<BinaryOperators, Type*>, Type*> binaryOperators;
            std::map<UnaryOperators, Type*> unaryOperators;
        protected:
            Type(KindOfType t, llvm::Type* llvmType, std::map<std::pair<BinaryOperators, Type*>, Type*>&& bO, std::map<UnaryOperators, Type*>&& uO) 
                : kind(t), llvmType(llvmType), binaryOperators(std::move(bO)), unaryOperators(std::move(uO)) {}
            Type() {};
        public:
            //static Type* typeOfExpression(const AST::Expression& expr);
            inline llvm::Type* getLLVMType() const {return llvmType;}
            inline void addBinaryOp(std::pair<BinaryOperators, Type*> op, Type* result) {binaryOperators[op] = result;}
            inline void addUnaryOp(UnaryOperators op, Type* result) {unaryOperators[op] = result;}
            inline Type* resultOfOperation(std::pair<BinaryOperators, Type*> op) const {return binaryOperators[op];}
            inline Type* resultOfOperation(UnaryOperators op) const {return unaryOperators[op];}

            
    };

    class BasicType : public Type {
        public:
            enum class Kind {
                INT,
                FLOAT,
                DOUBLE,
                BOOL
            };
        private:
            Kind kind;
        public:
            BasicType(Kind k); 

    };

    class RecordType : public Type {
        private:
            std::map<std::string, Type*> members;
        public:
            RecordType(std::map<std::string, Type*> members) : members(members) {}

    };

    class UndecidedType : public Type {
        std::vector<Type*> getTypesThatMatchCurrentState();
    };

    class TypeTable {
        private:
            std::map<std::string, Type*> types;

        public:
            inline Type* getType(const std::string& name) {return types[name];}
            inline void addType(const std::string& name, Type* t) {types[name] = t;}
            ~TypeTable();
    };

};