#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "include/lexer/Lexer.h"
#include "include/parser/Parser.h"
#include "interpreter/ExecutionData.h"
#include "data/DatabaseStructure.h"

void createInformationSchema();

int main() {

    std::string request;
    ExecutionData *executionData = new ExecutionData();

    createInformationSchema();

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

void createInformationSchema() {

    if (mkdir(DatabaseStructure::BASE_DATA_PATH.c_str(), 0777) == -1) {
        if( errno != EEXIST ) {
            throw std::runtime_error(strerror(errno));
        }
    }

    if (mkdir((DatabaseStructure::BASE_DATA_PATH + "information_schema").c_str(), 0777) == -1) {
        if( errno != EEXIST ) {
            throw std::runtime_error(strerror(errno));
        }
    }

    std::ofstream Tables(DatabaseStructure::BASE_DATA_PATH + "information_schema/columns");
    Tables.close();
}

/*
 * CREATE TABLE aaa@test (id INT);
 */