//
// Created by nono on 16/10/2023.
//
#include "Field.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../structure/ColumnReference.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"
#include "../../../error/Error.h"
#include "ConstStringField.h"
#include "../../../lexer/symbol/value/NumberSymbol.h"
#include "ConstNumberField.h"
#include "../../../lexer/symbol/value/StringSymbol.h"
#include "../function/FunctionField.h"

std::vector<Field *> Field::createListField(const std::vector<Symbol *> &symbols) {
    std::vector<Field *> listFields;
    Field *tmpField;
    std::vector<Symbol *> tmpSymbolList;

    for (int start = 0; start < symbols.size(); start += (int) tmpSymbolList.size() + 1) {
        tmpSymbolList = getSymbolsBeforeComma(symbols, start);
        tmpField = convertToField(tmpSymbolList);
        listFields.push_back(tmpField);
    }

    return listFields;
}

std::vector<Symbol *> Field::getSymbolsBeforeComma(const std::vector<Symbol *> &symbols, int start) {
    std::vector<Symbol *> symbolList;
    int parenthesis = 0;

    for (int i = start; i < symbols.size(); i++) {
        if (symbols[i]->symbolValueType == s_Delimiter) {
            if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisLeft) {
                parenthesis += 1;
                symbolList.push_back(symbols[i]);
                continue;
            }
            if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisRight) {
                parenthesis -= 1;
                if (parenthesis < 0) {
                    Error::syntaxError(")");
                }
                symbolList.push_back(symbols[i]);
                continue;
            }
            if (parenthesis == 0 && ((DelimiterSymbol *) symbols[i])->keyword == v_Comma) {
                return symbolList;
            }
        }

        symbolList.push_back(symbols[i]);
    }

    return symbolList;
}

Field *Field::convertToField(const std::vector<Symbol *> &symbols) {
    Field *field;

    field = tryConvertToColumnReference(symbols);
    if (field == nullptr) {
        field = tryConvertToConst(symbols);
    }
    if (field == nullptr) {
        field = tryConvertToFunction(symbols);
    }
    if (field == nullptr) {
        field = tryConvertToOperation(symbols);
    }
    if (field == nullptr) {
        field = tryConvertToStatement(symbols);
    }

    if (field == nullptr) {
        Error::syntaxError(symbols[0]);
    }

    return field;
}

Field *Field::tryConvertToColumnReference(const std::vector<Symbol *> &symbols) {
    ColumnReference *columnReference;

    if (symbols.empty()) {
        return nullptr;
    }

    if (symbols[0]->symbolValueType != s_Identifier) {
        return nullptr;
    }

    if (symbols.size() == 1) {
        columnReference = new ColumnReference(((IdentifierSymbol *) symbols[0])->value);
    } else if (symbols.size() == 3) {
        if (symbols[1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[1])->keyword != v_Dot ||
            symbols[2]->symbolValueType != s_Identifier) {
            return nullptr;
        }
        columnReference = new ColumnReference(((IdentifierSymbol *) symbols[2])->value,
                                              ((IdentifierSymbol *) symbols[0])->value);
    } else {
        return nullptr;
    }

    return columnReference;
}

Field *Field::tryConvertToConst(const std::vector<Symbol *> &symbols) {
    Field *constField = nullptr;

    if (symbols.size() == 1) {
        if (symbols[0]->symbolValueType == s_Number) {
            constField = new ConstNumberField(((NumberSymbol *) symbols[0])->value);
        } else if (symbols[0]->symbolValueType == s_String) {
            constField = new ConstStringField(((StringSymbol *) symbols[0])->value);
        }
    }

    return constField;
}

Field *Field::tryConvertToFunction(const std::vector<Symbol *> &symbols) {
    int functionType;
    Field *field;

    if (symbols.size() < 3) return nullptr;
    if (symbols[0]->symbolValueType != s_Keyword) return nullptr;
    if (symbols[1]->symbolValueType != s_Delimiter
        || ((DelimiterSymbol *) symbols[1])->keyword != v_ParenthesisLeft
        || symbols[symbols.size() - 1]->symbolValueType != s_Delimiter
        || ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword != v_ParenthesisRight) {
        return nullptr;
    }

    functionType = FunctionField::tryConvertToFunctionEnum(((KeywordSymbol *) symbols[0])->keyword);

    if (functionType == -1) return nullptr;

    field = new FunctionField(functionType);

    return field;
}

Field *Field::tryConvertToStatement(const std::vector<Symbol *> &symbols) {
    return nullptr;
}

Field *Field::tryConvertToOperation(const std::vector<Symbol *> &symbols) {
    return nullptr;
}
