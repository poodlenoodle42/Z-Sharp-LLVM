#include <iostream>
#include <string>
#include <fstream>
#include "ParserDriver.hpp"
#include "Printer.hpp"
int main(int argc, char** argv) {
    std::string inputFilename("test.zs");
    std::ifstream file_stream(inputFilename);

    ParserDriver driver(inputFilename, file_stream);
    int result = driver.parse();

    if (result == 0) {
        std::cout << "Successfully parsed\n";
        Visitor::Printer printer;
        driver.getAST().accept(printer);
    } else {
        std::cout << "Error parsing\n";
        return 1;
    }

}