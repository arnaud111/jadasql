//
// Created by nono on 10/10/23.
//

#include <stdexcept>
#include <string.h>
#include "Parser.h"

std::vector<Statement*> Parser::parse(std::vector<Symbol> symbols) {
    std::vector<Statement*> listStatement;
    Statement *statement = nullptr;

    for (int i = 0; i < symbols.size(); i++) {
        if (statement == nullptr) {
            statement = createStatement(symbols[i]);
        }
    }

    return listStatement;
}

Statement *Parser::createStatement(Symbol symbol) {
    Statement* statement;

    if (symbol.group == g_StatementKeyword) {

    }
/*
    if (statement == nullptr) {
        throw invalid_argument("Syntax Error");
    }
*/
    return statement;
}
