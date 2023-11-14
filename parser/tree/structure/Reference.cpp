//
// Created by nono on 14/11/2023.
//

#include <vector>
#include "TableReference.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"
#include "../../../error/Error.h"

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
