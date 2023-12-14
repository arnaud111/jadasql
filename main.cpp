#include <iostream>
#include "include/lexer/Lexer.h"
#include "include/parser/Parser.h"
#include "interpreter/ExecutionData.h"

int main() {

    std::string request;
    ExecutionData *executionData = new ExecutionData();

    while (true) {

        printf(">>> ");
        std::getline(std::cin, request);

        if (request == "exit") {
            break;
        }

        Lexer lexicalScanner = Lexer();
        vector<Symbol *> result = lexicalScanner.scan(request);
        vector<Statement *> listStatement = Parser::parse(result);

        for (auto &statement: listStatement) {
            ReturnedValue *returnedValue = statement->execute(executionData);
            if (returnedValue != nullptr) {
                returnedValue->display();
            }
        }
    }

    printf("Bye <3\n");
    return 0;
}
