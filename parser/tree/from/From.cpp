//
// Created by nono on 16/10/2023.
//
#include "From.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../error/Error.h"
#include "../statements/Statement.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"

From::From(const std::vector<Symbol *> &symbols) {
    std::vector<Symbol *> symbolList;
    unsigned long long index = 0;

    if (symbols.empty()) {
        Error::syntaxError("FROM");
    }

    symbolList = Statement::splitUntilKeywords(symbols, 0);
    this->table = new TableReference(symbolList);
    index += symbolList.size();

    while (index < symbols.size()) {
        symbolList = Statement::splitUntilKeywords(symbols, index + 1, {k_Left, k_Right, k_Inner});
        symbolList.insert(symbolList.begin(), symbols[index]);
        this->listJoint.push_back(new Joint(symbolList));
        index += symbolList.size() + 1;
    }
}
