//
// Created by nono on 14/11/2023.
//

#include "ColumnDetail.h"
#include "../../../error/Error.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"
#include "../statements/Statement.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"
#include "../field/NullField.h"
#include "../field/ConstStringField.h"
#include "../../../lexer/symbol/value/StringSymbol.h"

ColumnDetail::ColumnDetail(std::vector<Symbol *> symbols) {

    std::vector<Symbol *> tmpSymbolList;
    unsigned long long index = 0;

    this->columnCreationType = t_ColumnDetail;
    this->dataType = nullptr;
    this->name = nullptr;
    this->notNull = false;
    this->defaultValue = nullptr;
    this->autoIncrement = false;

    if (symbols.size() < 2) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[index]->symbolValueType == s_Identifier) {
        this->name = new ColumnReference(((IdentifierSymbol *) symbols[index])->value);
    }
    if (this->name == nullptr) {
        Error::syntaxError(symbols[index]);
    }
    index++;

    tmpSymbolList = Statement::splitUntilKeywords(symbols, index, {k_AutoIncrement, k_Not, k_Default});

    this->dataType = DataType::convertToDataType(tmpSymbolList);
    if (this->dataType == nullptr) {
        Error::syntaxError(tmpSymbolList[tmpSymbolList.size() - 1]);
    }
    index += tmpSymbolList.size();

    if (symbols.size() == index) return;

    if (symbols[index]->symbolValueType != s_Keyword) {
        Error::syntaxError(symbols[index]);
    }

    if (((KeywordSymbol *) symbols[index])->keyword == k_Not) {
        if (symbols.size() != index + 1 && symbols[index + 1]->symbolValueType == s_Keyword && ((KeywordSymbol *) symbols[index + 1])->keyword == k_Null) {
            this->notNull = true;
            index += 2;
        }
    }

    if (symbols.size() == index) return;

    if (((KeywordSymbol *) symbols[index])->keyword == k_Default) {
        if (symbols.size() != index + 1) {
            if (symbols[index + 1]->symbolValueType == s_Keyword) {
                if (((KeywordSymbol *) symbols[index + 1])->keyword == k_Null) {
                    this->defaultValue = new NullField();
                    index += 2;
                }
            } else if (symbols[index + 1]->symbolValueType == s_String) {
                this->defaultValue = new ConstStringField(((StringSymbol *) symbols[index + 1])->value);
                index += 2;
            }
        }
    }

    if (symbols.size() == index) return;

    if (((KeywordSymbol *) symbols[index])->keyword == k_AutoIncrement) {
        this->autoIncrement = true;
        index++;
    }

    if (index != symbols.size()) {
        Error::syntaxError(symbols[index]);
    }
}
