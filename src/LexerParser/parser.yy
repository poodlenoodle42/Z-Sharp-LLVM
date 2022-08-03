%skeleton "lalr1.cc" //Use C++ skeleton

%require "3.5" //Use new version, supports c++ and does not create legacy files like position.hh
%language "c++" //Well, I mean....
%locations //Generate Location type for better diagnostics
%header
%define api.value.automove //Auto moves values of terminals/nonterminals (e.g. $1), needed for easy use of unique_ptr
%define api.value.type variant //Use real c++ types as types for terminals and nonterminals, more typesafe than %union
%define api.token.constructor //Define functions to construct token types, makes tokens type safe  
%define api.token.raw //Disables conversion between internal and external token numbers, charachter tokens like '+' can not be created anymore
%define parse.assert //Checks that symbols are constructed and destroyed properly, uses RTTI
%define api.parser.class { Parser }


%code requires {
    #include "location.hh"
    #include <string>
    #include <iostream>
    #include <memory>
    #include <vector>
    #include "AST.hpp"

    class ParserDriver;
    namespace yy {class Scanner;}
}
%define api.location.type {yy::location}

%lex-param {yy::Scanner& scanner}
%parse-param {ParserDriver& drv} //Pass the driver as a parameter to yyparse so he can be used in semantic actions
%parse-param {Scanner& scanner}
//Good syntax error messages
%define parse.trace
%define parse.error detailed
%define parse.lac full

%code {
    #include "ParserDriver.hpp"
    #include "Scanner.hpp"
    #include <utility>

    static yy::Parser::symbol_type yylex(yy::Scanner& scanner) {
        return scanner.get_next_token();
    }
}

%token FUNC 
%token LBRACE "{" RBRACE "}" LPAREN "(" RPAREN ")" COMMA ","
%token NEWLINE "\n"
%token <std::string> IDENTIFIER

%nterm <AST::StmtPtr> stmt
%nterm <std::vector<AST::StmtPtr>> stmtList
%nterm <std::unique_ptr<AST::BlockStmt>> block
%nterm <std::vector<std::string>> idList
%nterm <std::unique_ptr<AST::Function>> function
%nterm top_level_list top_level_item

%start program
%%

program: top_level_list;

top_level_list: 
  top_level_item "\n"
| top_level_item YYEOF
;

top_level_item: 
  function      {drv.getAST().addFunction($1);}
;

function : FUNC IDENTIFIER "(" idList ")" block {$$ = std::make_unique<AST::Function>($2, $4, $6);}
;

block :
  "{" "\n" stmtList "}"     {$$ = std::make_unique<AST::BlockStmt>(@$, $3);}
| "\n" "{" "\n" stmtList "}"{$$ = std::make_unique<AST::BlockStmt>(@$, $4);}
;

stmt : block "\n" {$$ = $1;}
;

stmtList : 
  stmtList stmt    {auto v = $1; v.push_back($2); $$ = std::move(v);}
| %empty                {$$ = std::vector<AST::StmtPtr>();}
;

idList : 
  idList "," IDENTIFIER {auto v = $1; v.push_back($3); $$ = std::move(v);}
| IDENTIFIER            {$$ = std::vector<std::string>(); $$.push_back($1);}
| %empty                {$$ = std::vector<std::string>();}
;
%%

void
yy::Parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}