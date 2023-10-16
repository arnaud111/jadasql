//
// Created by nono on 16/10/2023.
//

#include <stdexcept>
#include "SelectStatement.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"
#include "../../../lexer/symbol/value/NumberSymbol.h"

SelectStatement::SelectStatement(const std::vector<Symbol *>& symbols) : Statement() {
    std::vector<Symbol *> splitSymbols;
    int index = 1;

    if (symbols.size() < 2) {
        throw std::invalid_argument("Syntax Error");
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

    if (((KeywordSymbol*) symbols[index])->keyword == v_From) {
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Where, v_Group, v_Order, v_Limit});
        this->from = new From(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol*) symbols[index])->keyword == v_Where) {
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Group, v_Order, v_Limit});
        this->where = new Condition(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol*) symbols[index])->keyword == v_Group) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Keyword || ((KeywordSymbol*) symbols[index])->keyword != v_By) {
            throw std::invalid_argument("Syntax Error");
        }
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Order, v_Limit});
        this->groupBy = Field::createListField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol*) symbols[index])->keyword == v_Order) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Keyword || ((KeywordSymbol*) symbols[index])->keyword != v_By) {
            throw std::invalid_argument("Syntax Error");
        }
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {v_Limit});
        this->orderBy = Field::createListField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol*) symbols[index])->keyword == v_Limit) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Number) {
            throw std::invalid_argument("Syntax Error");
        }
        this->limit = ((NumberSymbol *) symbols[index])->value;
        if (this->limit < 0) {
            throw std::invalid_argument("Syntax Error");
        }
    }

    if (index + 1 != symbols.size()) throw std::invalid_argument("Syntax Error");
}

bool SelectStatement::isDistinct(std::vector<Symbol *> symbols) {
    if (symbols[1]->symbolValueType == s_Keyword) {
        if (((KeywordSymbol*) symbols[1])->keyword == v_Distinct) {
            return true;
        }
        throw std::invalid_argument("Syntax Error");
    }
    return false;
}
