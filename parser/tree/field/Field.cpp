//
// Created by nono on 16/10/2023.
//
#include "Field.h"
#include "../function/Function.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../structure/ColumnReference.h"
#include "../../../lexer/symbol/value/IdentifierSymbol.h"
#include "../../../error/Error.h"
#include "ConstStringField.h"
#include "../../../lexer/symbol/value/NumberSymbol.h"
#include "ConstNumberField.h"
#include "../../../lexer/symbol/value/StringSymbol.h"
#include "../function/LeftFunction.h"
#include "../function/RightFunction.h"
#include "../function/MaxFunction.h"
#include "../function/MinFunction.h"
#include "../function/SumFunction.h"
#include "../function/CountFunction.h"
#include "../function/ConcatFunction.h"
#include "../function/FormatFunction.h"
#include "../function/AvgFunction.h"
#include "../function/IfNullFunction.h"
#include "../function/CoalesceFunction.h"
#include "../../Parser.h"

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

    functionType = Function::tryConvertToFunctionEnum(((KeywordSymbol *) symbols[0])->keyword);

    if (functionType == -1) return nullptr;

    field = Field::tryConvertToFunctionField(symbols, functionType);

    return field;
}

Field *Field::tryConvertToStatement(const std::vector<Symbol *> &symbols) {
    std::vector<Symbol *> listSymbolStatement;

    if (symbols.size() < 3) return nullptr;
    if (symbols[0]->symbolValueType != s_Delimiter
        || symbols[symbols.size() - 1]->symbolValueType != s_Delimiter
        || ((DelimiterSymbol *) symbols[0])->keyword != v_ParenthesisLeft
        || ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword != v_ParenthesisRight
        || symbols[1]->symbolValueType != s_Statement ) {
        return nullptr;
    }

    for (int i = 1; i < symbols.size() - 1 ; i++) {
        listSymbolStatement.push_back(symbols[i]);
    }

    return Parser::createStatement(listSymbolStatement);
}

Field *Field::tryConvertToOperation(const std::vector<Symbol *> &symbols) {


    return nullptr;
}

Field *Field::tryConvertToFunctionField(const std::vector<Symbol *> &symbols, int function) {
    std::vector<Symbol *> listSymbolInArgument;
    std::vector<Field *> listField;

    for (int i = 2; i < symbols.size() - 1; i++) {
        listSymbolInArgument.push_back(symbols[i]);
    }

    listField = Field::createListField(listSymbolInArgument);

    switch (function) {
        case f_Left:
            if (listField.size() != 2) return nullptr;
            return new LeftFunction(listField[0], listField[1]);
        case f_Right:
            if (listField.size() != 2) return nullptr;
            return new RightFunction(listField[0], listField[1]);
        case f_Max:
            if (listField.size() != 1) return nullptr;
            return new MaxFunction(listField[0]);
        case f_Min:
            if (listField.size() != 1) return nullptr;
            return new MinFunction(listField[0]);
        case f_Sum:
            if (listField.size() != 1) return nullptr;
            return new SumFunction(listField[0]);
        case f_Count:
            if (listField.size() != 1) return nullptr;
            return new CountFunction(listField[0]);
        case f_Concat:
            return new ConcatFunction(listField);
        case f_Format:
            if (listField.size() != 2) return nullptr;
            return new FormatFunction(listField[0], listField[1]);
        case f_Avg:
            if (listField.size() != 1) return nullptr;
            return new AvgFunction(listField[0]);
        case f_IfNull:
            if (listField.size() != 2) return nullptr;
            return new IfNullFunction(listField[0], listField[1]);
        case f_Coalesce:
            return new CoalesceFunction(listField);
        default:
            break;
    }

    return nullptr;
}
