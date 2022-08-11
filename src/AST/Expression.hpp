#pragma once
#include "Visitor.hpp"
#include "location.hh"
#include <string>
#include <vector>
#include <memory>
namespace AST {
    class Expression {
        yy::location location;
        public:
            Expression(yy::location loc) : location(loc) {}
            inline yy::location getLocation() {return location;}
            virtual ~Expression() {}
            virtual void accept(Visitor& vis) = 0;
    };

    typedef std::unique_ptr<Expression> ExprPtr;

    class BinaryExpr : public Expression {
        public:
            enum class Type {
                PLUS,
                MINUS,
                MULT,
                DIV,
                EQUALSEQUALS,
                GREATER,
                LESS,
                GREATER_EQUALS,
                LESS_EQUALS
            };
        private:
            Type type;
        public:
            ExprPtr left, right;
            BinaryExpr(yy::location loc, ExprPtr left, ExprPtr right, Type type) 
                : Expression(loc), type(type), left(std::move(left)), right(std::move(right)) {}
            void accept(Visitor& vis) override {vis.visitBinary(*this);}
            Type getType() const {return type;}
    };

    class UnaryExpr : public Expression {
        public:
            enum class Type {
                NOT,
                NEGATE
            };
        private:
            Type type;
        public:
            ExprPtr expr;
            UnaryExpr(yy::location loc, ExprPtr expr, Type type) 
                : Expression(loc), type(type), expr(std::move(expr)) {}
            void accept(Visitor& vis) override {vis.visitUnary(*this);}
            Type getType() const {return type;}
    };

    class NumberLiteral : public Expression {
        union {
            int i;
            double d;
        };
        public:
            enum class Type {
                DOUBLE,
                INTEGER,
            };
        private:
            Type type;
        public:
            NumberLiteral(yy::location loc, int i) : Expression(loc), i(i), type(Type::INTEGER) {}
            NumberLiteral(yy::location loc, double d) : Expression(loc), d(d), type(Type::DOUBLE) {}
            void accept(Visitor& vis) override {vis.visitNumberLiteral(*this);}
            Type getType() const {return type;}
            int getInt() const {return i;}
            double getDouble() const {return d;}
    };

    class StringLiteral : public Expression {
        std::string string;
        public:
            StringLiteral(yy::location loc, std::string&& string) : Expression(loc), string(std::move(string)) {}
            void accept(Visitor& vis) override {vis.visitStringLiteral(*this);}
            std::string_view getString() const {return string;}
    };

    class BoolLiteral : public Expression {
        bool value;
        public:
            BoolLiteral(yy::location loc, bool value) : Expression(loc), value(value) {}
            void accept(Visitor& vis) override {vis.visitBoolLiteral(*this);}
            bool getValue() const {return value;}
    };

    class Identifier : public Expression {
        std::string name;
        public:
            Identifier(yy::location loc, std::string&& name) : Expression(loc), name(std::move(name)) {}
            void accept(Visitor& vis) override {vis.visitIdentifier(*this);}
            std::string_view getString() const {return name;}
    };

    class CallExpr : public Expression {
        std::string callee;
        public:
            std::vector<ExprPtr> arguments;
            CallExpr(yy::location loc, std::string&& callee, std::vector<ExprPtr> arguments) 
                : Expression(loc), callee(std::move(callee)), arguments(std::move(arguments)) {}
            void accept(Visitor& vis) override {vis.visitCallExpr(*this);}
            std::string_view getCallee() const {return callee;}
    };
};