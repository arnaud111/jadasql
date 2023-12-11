#include <iostream>
#include "include/lexer/Lexer.h"
#include "include/parser/Parser.h"

int main() {

    std::string request;

    while (true) {

        printf(">> ");
        std::getline(std::cin, request);

        if (request == "exit") {
            break;
        }

        Lexer lexicalScanner = Lexer();
        vector<Symbol *> result = lexicalScanner.scan(request);
        vector<Statement *> listStatement = Parser::parse(result);
    }

    printf("Bye <3\n");
    return 0;
}
