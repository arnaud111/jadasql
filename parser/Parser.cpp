//
// Created by nono on 10/10/23.
//

#include <stdexcept>
#include "Parser.h"
#include "../lexer/symbol/keyword/StatementSymbol.h"
#include "tree/statements/SelectStatement.h"
#include "../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../lexer/symbol/keyword/KeywordSymbol.h"

std::vector<Statement*> Parser::parse(const std::vector<Symbol*>& symbols) {
    std::vector<Statement*> listStatement;
    std::vector<std::vector<Symbol *>> listRequest = Parser::splitRequests(symbols);

    listStatement.reserve(listRequest.size());
    for (const auto & i : listRequest) {
        listStatement.push_back(Parser::createStatement(i));
    }

    return listStatement;
}

std::vector<std::vector<Symbol *>> Parser::splitRequests(const std::vector<Symbol *>& symbols) {

    std::vector<std::vector<Symbol *>> listRequest;
    std::vector<Symbol*> tmp;

    for (auto & symbol : symbols) {
        if (symbol->symbolValueType == s_Delimiter && ((DelimiterSymbol*) symbol)->keyword == v_SemiColon) {
            listRequest.push_back(tmp);
            tmp = {};
        } else {
            tmp.push_back(symbol);
        }
    }

    if (!tmp.empty()) {
        listRequest.push_back(tmp);
    }

    return listRequest;
}

Statement* Parser::createStatement(std::vector<Symbol*> symbols) {
    Statement* statement = nullptr;

    if (symbols[0]->symbolValueType != s_Statement) {
        throw std::invalid_argument("Syntax Error");
    }

    switch (((StatementSymbol*) symbols[0])->keyword) {
        case v_Select:
            statement = new SelectStatement(symbols);
            break;
        case v_Update:
            break;
        case v_Delete:
            break;
        case v_Drop:
            break;
        case v_Insert:
            break;
        case v_Create:
            break;
        case v_Alter:
            break;
    }

    return statement;
}
