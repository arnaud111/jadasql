//
// Created by nono on 20/11/2023.
//

#include "../../../include/parser/tree/from/Joint.h"
#include "../../../include/error/Error.h"
#include "../../../include/lexer/symbol/keyword/KeywordSymbol.h"
#include "../../../include/parser/tree/statements/Statement.h"

Joint::Joint(std::vector<Symbol *> symbols) {

    this->table = nullptr;
    this->joinType = InnerJoin;
    this->on = nullptr;

    std::vector<Symbol *> tmpSymbolList;

    if (symbols.size() < 5) {
        Error::syntaxError(symbols[0]);
    } if (symbols[0]->symbolValueType != s_Keyword) {
        Error::syntaxError(symbols[0]);
    } if (symbols[1]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[1])->keyword != k_Join) {
        Error::syntaxError(symbols[1]);
    }

    if (((KeywordSymbol *) symbols[0])->keyword == k_Left) {
        this->joinType = LeftJoin;
    } else if (((KeywordSymbol *) symbols[0])->keyword == k_Right) {
        this->joinType = RightJoin;
    } else if (((KeywordSymbol *) symbols[0])->keyword == k_Inner) {
        this->joinType = InnerJoin;
    } else {
        Error::syntaxError(symbols[0]);
    }

    tmpSymbolList = Statement::splitUntilKeywords(symbols, 2, {k_On});

    if (tmpSymbolList.size() + 2 == symbols.size()) Error::syntaxError(symbols[2]);

    this->table = new TableReference(tmpSymbolList);

    if (symbols[tmpSymbolList.size() + 2]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[tmpSymbolList.size() + 2])->keyword != k_On) {
        Error::syntaxError(symbols[tmpSymbolList.size() + 2]);
    }

    tmpSymbolList = Statement::cut_symbol_vector(symbols, tmpSymbolList.size() + 3, symbols.size());
    this->on = Field::convertToField(tmpSymbolList);
}
