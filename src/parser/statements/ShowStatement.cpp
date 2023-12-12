//
// Created by nono on 12/12/23.
//

#include "../../../include/parser/tree/statements/ShowStatement.h"
#include "error/Error.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"


ShowStatement::ShowStatement(std::vector<Symbol *> symbols) {

    if (symbols.size() != 2) {
        Error::syntaxError(symbols[0]);
    }

    switch (((KeywordSymbol *) symbols[1])->keyword) {
        case k_Databases:
            this->type = ShowDatabases;
            break;
        case k_Tables:
            this->type = ShowTables;
            break;
        default:
            Error::syntaxError(symbols[1]);
            break;
    }
}

ReturnedValue *ShowStatement::execute() {
    return nullptr;
}
