//
// Created by nono on 14/11/2023.
//

#include "Assign.h"
#include "../../../error/Error.h"
#include "../../../lexer/symbol/keyword/OperatorSymbol.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"

Assign::Assign(std::vector<Symbol *> symbols) {
    this->column = nullptr;
    this->value = nullptr;

    if (symbols.size() < 3) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[0]->symbolValueType != s_Identifier) {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Operator || ((OperatorSymbol *) symbols[1])->keyword != v_Equal) {
        Error::syntaxError(symbols[1]);
    }

    this->column = new ColumnReference(((IdentifierSymbol *) symbols[0])->value);
    this->value = Field::convertToField(Field::cut_symbol_vector(symbols, 2, symbols.size()));
}

std::vector<Assign *> Assign::convert_to_list_assign(std::vector<Symbol *> symbols) {
    std::vector<Assign *> list;
    Assign *tmpAssign;
    std::vector<Symbol *> tmpSymbolList;

    for (int start = 0; start < symbols.size(); start += (int) tmpSymbolList.size() + 1) {
        tmpSymbolList = Field::getSymbolsBeforeComma(symbols, start);
        tmpAssign = new Assign(tmpSymbolList);
        list.push_back(tmpAssign);
    }

    return list;
}
