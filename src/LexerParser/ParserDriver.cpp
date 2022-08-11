#include "ParserDriver.hpp"
#include "Scanner.hpp"
#include "parser.tab.hpp"
ParserDriver::ParserDriver(std::string file_name,std::istream& input_stream)
    : scanner(new yy::Scanner(*this, input_stream)), parser(new yy::Parser(*this,*scanner)) , file_name(file_name) {}

ParserDriver::ParserDriver()   
    : scanner(new yy::Scanner(*this)), parser(new yy::Parser(*this, *scanner)), file_name("terminal") {}

ParserDriver::~ParserDriver() {
    delete parser;
    delete scanner;
    parser = nullptr;
    scanner = nullptr;
}
int ParserDriver::parse() {
    if (parser == nullptr || scanner == nullptr) {
        std::cerr << "Parser or scanner not correctly initialized\n";
        return 2;
    }
    return (*(this->parser))();
}
