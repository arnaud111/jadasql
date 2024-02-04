#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "include/lexer/Lexer.h"
#include "include/parser/Parser.h"
#include "interpreter/ExecutionData.h"
#include "data/DatabaseStructure.h"
#include "data/InformationSchemaLine.h"
#include "data/TableStructure.h"

void createInformationSchema();

int main() {

    std::string request;
    auto *executionData = new ExecutionData();

    createInformationSchema();
    std::vector<InformationSchemaLine *> columnsInformation = InformationSchemaLine::get_all_information_schema();


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

    if (!TableStructure::tableExist("information_schema", "columns")) {
        std::ofstream Tables(DatabaseStructure::BASE_DATA_PATH + "information_schema/columns");
        Tables.close();
    }
}

/*
 * CREATE TABLE aaa@user (id INT, age INT);
 * INSERT INTO aaa@user VALUES (1, 1);
 */