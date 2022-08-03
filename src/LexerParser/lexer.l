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
"("                     return yy::Parser::make_LPAREN(loc);
")"                     return yy::Parser::make_RPAREN(loc);
"{"                     return yy::Parser::make_LBRACE(loc);
"}"                     return yy::Parser::make_RBRACE(loc);
","                     return yy::Parser::make_COMMA(loc);
{identifier}            return yy::Parser::make_IDENTIFIER(yytext, loc);
<<EOF>>                 return yy::Parser::make_YYEOF(loc);
%%

yy::Scanner::Scanner(ParserDriver& driver) : driver(driver), yyFlexLexer(&std::cin) {loc.initialize(&driver.get_file_name());}
yy::Scanner::Scanner(ParserDriver& driver, std::istream& in) : driver(driver), yyFlexLexer(&in) {loc.initialize(&driver.get_file_name());} 