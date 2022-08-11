%{
    #include <string>
        
    #include "ParserDriver.hpp"
    #include "parser.tab.hpp"
    #include "Scanner.hpp"

    #define YY_USER_ACTION loc.columns(yyleng);
    
%}


%option noyywrap nounput noinput debug c++
%option yyclass="yy::Scanner"
%option prefix="yy_"

identifier  [a-zA-z][a-zA-Z0-9]* 
number      [0-9]
%% 

%{
    //yy::location& loc = drv.location;
    loc.step();
%}
\/\/.* ; //Comment
[\t \r] loc.step();
"\n"                    loc.lines(1); return yy::Parser::make_NEWLINE(loc);
"func"                  return yy::Parser::make_FUNC(loc);
"false"                 return yy::Parser::make_FALSE(loc);
"true"                  return yy::Parser::make_TRUE(loc);
"if"                    return yy::Parser::make_IF(loc);
"else"                  return yy::Parser::make_ELSE(loc);
"("                     return yy::Parser::make_LPAREN(loc);
")"                     return yy::Parser::make_RPAREN(loc);
"{"                     return yy::Parser::make_LBRACE(loc);
"}"                     return yy::Parser::make_RBRACE(loc);
","                     return yy::Parser::make_COMMA(loc);
"+"                     return yy::Parser::make_PLUS(loc);
"-"                     return yy::Parser::make_MINUS(loc);
"*"                     return yy::Parser::make_STAR(loc);
"/"                     return yy::Parser::make_SLASH(loc);
"!"                     return yy::Parser::make_NOT(loc);
"=="                    return yy::Parser::make_EQUALSEQUALS(loc);
">"                     return yy::Parser::make_GREATER(loc);
"<"                     return yy::Parser::make_LESS(loc);
">="                    return yy::Parser::make_GREATEREQUALS(loc);
"<="                    return yy::Parser::make_LESSEQUALS(loc);
\"([^\\\"]|\\.)*\"      {std::string s = yytext; return yy::Parser::make_STRING_LITERAL(s.substr(1,s.size()-2),loc);}
{identifier}            return yy::Parser::make_IDENTIFIER(yytext, loc);
{number}*\.{number}+    return yy::Parser::make_DOUBLE_LITERAL(std::stod(yytext), loc);
{number}+\.{number}*    return yy::Parser::make_DOUBLE_LITERAL(std::stod(yytext), loc);
{number}+               return yy::Parser::make_INTEGER_LITERAL(std::atoi(yytext), loc);
<<EOF>>                 return yy::Parser::make_YYEOF(loc);
%%

yy::Scanner::Scanner(ParserDriver& driver) : yyFlexLexer(&std::cin), driver(driver) {loc.initialize(&driver.get_file_name());}
yy::Scanner::Scanner(ParserDriver& driver, std::istream& in) : yyFlexLexer(&in), driver(driver) {loc.initialize(&driver.get_file_name());} 