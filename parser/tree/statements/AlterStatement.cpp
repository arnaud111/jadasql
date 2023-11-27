//
// Created by nono on 13/11/2023.
//

#include "AlterStatement.h"
#include "../../../error/Error.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"
#include "../../../lexer/symbol/keyword/StatementSymbol.h"

AlterStatement::AlterStatement(std::vector<Symbol *> symbols) {

    std::vector<Symbol *> tmpSymbolList;
    this->table = nullptr;

    if (symbols.size() < 5) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[1]->symbolValueType != s_Keyword || ((KeywordSymbol *)symbols[1])->keyword != k_Table) {
        Error::syntaxError(symbols[1]);
    }

    tmpSymbolList = Statement::splitUntilKeywords(symbols, 2, {k_Add, k_Modify, k_Change}, {v_Drop});

    this->table = new TableReference(tmpSymbolList);

    for (auto &m: Statement::splitComa(symbols, 2 + tmpSymbolList.size())) {
        this->modifications.push_back(new ColumnModification(m));
    }
}
