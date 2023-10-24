//
// Created by nono on 16/10/2023.
//

#include "SelectStatement.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"
#include "../../../lexer/symbol/value/NumberSymbol.h"
#include "../../../error/Error.h"

SelectStatement::SelectStatement(const std::vector<Symbol *> &symbols) : Statement() {
    std::vector<Symbol *> splitSymbols;
    int index = 1;

    if (symbols.size() < 2) {
        Error::syntaxError("SELECT");
    }

    this->statementType = Select;
    this->from = nullptr;
    this->where = nullptr;
    this->limit = -1;
    this->distinct = SelectStatement::isDistinct(symbols);

    if (this->distinct) {
        index = 2;
    }

    splitSymbols = SelectStatement::splitUntilKeywords(symbols, index, {v_From, v_Where, v_Group, v_Order, v_Limit});
    this->field = Field::createListField(splitSymbols);
    index += (int) splitSymbols.size();

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == v_From) {
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Where, v_Group, v_Order, v_Limit});
        this->from = new From(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == v_Where) {
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Group, v_Order, v_Limit});
        this->where = Field::convertToField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == v_Group) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Keyword ||
            ((KeywordSymbol *) symbols[index])->keyword != v_By) {
            Error::syntaxError("GROUP");
        }
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Order, v_Limit});
        this->groupBy = Field::createListField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == v_Order) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Keyword ||
            ((KeywordSymbol *) symbols[index])->keyword != v_By) {
            Error::syntaxError("ORDER");
        }
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Limit});
        this->orderBy = Field::createListField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == v_Limit) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Number) {
            Error::syntaxError("LIMIT");
        }
        this->limit = ((NumberSymbol *) symbols[index])->value;
        if (this->limit < 0) {
            Error::syntaxError("LIMIT");
        }
    }

    if (index + 1 != symbols.size()) {
        Error::syntaxError("After SELECT");
    }
}

bool SelectStatement::isDistinct(std::vector<Symbol *> symbols) {
    if (symbols[1]->symbolValueType == s_Keyword) {
        if (((KeywordSymbol *) symbols[1])->keyword == v_Distinct) {
            return true;
        }
        Error::syntaxError("SELECT");
    }
    return false;
}
