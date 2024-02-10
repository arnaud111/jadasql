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

    /*for (auto &col: columnsInformation) {
        col->display();
    }*/

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
        TableStructure::createTable("information_schema", "columns");
    }
}

/*
 * CREATE TABLE aaa@user_char (id INT, age INT, name CHAR(4));
 * INSERT INTO aaa@user_char VALUES (1, 1, "a");
 * SELECT id, age, name FROM aaa@user_char;
 * DELETE FROM aaa@user WHERE id = 1;
 * UPDATE aaa@user SET age = 2 WHERE id = 1;
 * DROP TABLE aaa@user;
 */