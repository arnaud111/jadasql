//
// Created by nono on 14/11/2023.
//

#include <vector>
#include "../../../include/parser/tree/structure/TableReference.h"
#include "../../../include/lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../include/lexer/symbol/value/IdentifierSymbol.h"
#include "../../../include/error/Error.h"
#include "parser/tree/structure/ColumnReference.h"

TableReference::TableReference(std::vector<Symbol *> symbols) {
    int index = 1;
    this->fieldType = f_Reference;
    this->databaseReference = nullptr;

    if (symbols[0]->symbolValueType == s_Identifier) {
        if (symbols.size() > 1 && symbols[1]->symbolValueType == s_Delimiter &&
            ((DelimiterSymbol *) symbols[1])->keyword == v_At) {
            if (symbols.size() < 3 || symbols[2]->symbolValueType != s_Identifier) {
                Error::syntaxError(((IdentifierSymbol *) symbols[0])->value);
            }
            this->tableName = ((IdentifierSymbol *) symbols[2])->value;
            this->databaseReference = new DatabaseReference(((IdentifierSymbol *) symbols[0])->value);
            index = 3;
        } else {
            this->tableName = ((IdentifierSymbol *) symbols[0])->value;
        }

        if (symbols.size() > index && symbols[index]->symbolValueType == s_Identifier) {
            this->alias = ((IdentifierSymbol *) symbols[index])->value;
        }
    }

    if (this->tableName.empty()) {
        Error::syntaxError(symbols[0]);
    }
}

DatabaseReference::DatabaseReference(std::vector<Symbol *> symbols) {

    if (symbols.size() != 1) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    } if (symbols[0]->symbolValueType != s_Identifier) {
        Error::syntaxError(symbols[0]);
    }

    this->databaseName = ((IdentifierSymbol *) symbols[0])->value;
}

DatabaseReference::DatabaseReference(std::string databaseName)  {
    this->databaseName = std::move(databaseName);
}

ReturnedValue *ColumnReference::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *DatabaseReference::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *TableReference::execute(ExecutionData *executionData) {
    return nullptr;
}
