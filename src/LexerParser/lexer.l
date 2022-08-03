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
#.* ; //Comment
[\t \r] loc.step();
"hello"                 return yy::Parser::make_HELLO("Hello",loc);
<<EOF>>                 return yy::Parser::make_YYEOF(loc);
%%

yy::Scanner::Scanner(ParserDriver& driver) : driver(driver), yyFlexLexer(&std::cin) {loc.initialize(&driver.get_file_name());}
yy::Scanner::Scanner(ParserDriver& driver, std::istream& in) : driver(driver), yyFlexLexer(&in) {loc.initialize(&driver.get_file_name());} 