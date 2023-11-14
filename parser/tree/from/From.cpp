//
// Created by nono on 16/10/2023.
//
#include "From.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../error/Error.h"

From::From(const std::vector<Symbol *> &symbols) {

    if (symbols.empty()) {
        Error::syntaxError("FROM");
    }

    this->table = new TableReference(symbols);
}
