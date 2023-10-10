//
// Created by nono on 10/10/23.
//

#include "Parser.h"
#include "tree/statements/SelectStatement.h"

std::vector<Statement*> Parser::parse(std::vector<Symbol> symbols) {
    std::vector<Statement*> listStatement;
    auto* selectStatement = new SelectStatement();

    listStatement.push_back(selectStatement);
    listStatement.push_back(new Statement());

    return listStatement;
}
