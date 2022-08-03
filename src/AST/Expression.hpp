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
            Expression(yy::location loc) : location(location) {}
            inline yy::location getLocation() {return location;}
            virtual ~Expression() {}
            virtual void accept(Visitor& vis) = 0;
    };

    typedef std::unique_ptr<Expression> ExprPtr;
};