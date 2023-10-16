//
// Created by nono on 16/10/2023.
//
#include <stdexcept>
#include "From.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"

From::From(const std::vector<Symbol *>& symbols) {

    if (symbols.empty()) {
        throw std::invalid_argument("Syntax Error");
    }

    this->table = getTableReference(symbols);
    if (this->table == nullptr) {
        throw std::invalid_argument("Syntax Error");
    }
}

TableReference *From::getTableReference(const std::vector<Symbol *> &symbols) {
    TableReference *tableReference = nullptr;
    int index = 1;

    if (symbols[0]->symbolValueType == s_Identifier) {
        if (symbols.size() > 1 && symbols[1]->symbolValueType == s_Delimiter && ((DelimiterSymbol*) symbols[1])->keyword == v_At) {
            if (symbols.size() < 3 || symbols[2]->symbolValueType == s_Identifier) {
                throw std::invalid_argument("Syntax Error");
            }
            tableReference = new TableReference(((IdentifierSymbol*) symbols[2])->value);
            tableReference->databaseReference = new DatabaseReference(((IdentifierSymbol*) symbols[0])->value);
            index = 3;
        } else {
            tableReference = new TableReference(((IdentifierSymbol*) symbols[0])->value);
        }

        if (symbols.size() > index && symbols[index]->symbolValueType == s_Identifier) {
            tableReference->alias = ((IdentifierSymbol*) symbols[index])->value;
        }
    }

    return tableReference;
}

