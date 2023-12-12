//
// Created by nono on 12/12/23.
//

#include "../../../include/parser/tree/statements/UseStatement.h"
#include "error/Error.h"
#include "lexer/symbol/value/IdentifierSymbol.h"


UseStatement::UseStatement(std::vector<Symbol *> symbols) {

    if (symbols.size() != 2) {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Identifier) {
        Error::syntaxError(symbols[1]);
    }

    this->database = new DatabaseReference(((IdentifierSymbol *) symbols[1])->value);
}

ReturnedValue *UseStatement::execute() {
    return nullptr;
}
