//
// Created by nono on 16/10/2023.
//
#include "../../../include/parser/tree/field/Field.h"
#include "../../../include/parser/tree/function/Function.h"
#include "../../../include/lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../include/parser/tree/structure/ColumnReference.h"
#include "../../../include/lexer/symbol/value/IdentifierSymbol.h"
#include "../../../include/error/Error.h"
#include "../../../include/parser/tree/field/ConstStringField.h"
#include "../../../include/lexer/symbol/value/NumberSymbol.h"
#include "../../../include/parser/tree/field/ConstNumberField.h"
#include "../../../include/lexer/symbol/value/StringSymbol.h"
#include "../../../include/parser/tree/function/LeftFunction.h"
#include "../../../include/parser/tree/function/RightFunction.h"
#include "../../../include/parser/tree/function/MaxFunction.h"
#include "../../../include/parser/tree/function/MinFunction.h"
#include "../../../include/parser/tree/function/SumFunction.h"
#include "../../../include/parser/tree/function/CountFunction.h"
#include "../../../include/parser/tree/function/ConcatFunction.h"
#include "../../../include/parser/tree/function/FormatFunction.h"
#include "../../../include/parser/tree/function/AvgFunction.h"
#include "../../../include/parser/tree/function/IfNullFunction.h"
#include "../../../include/parser/tree/function/CoalesceFunction.h"
#include "../../../include/parser/Parser.h"
#include "../../../include/lexer/symbol/keyword/OperatorSymbol.h"
#include "../../../include/parser/tree/operation/Operation.h"
#include "parser/tree/field/NullField.h"

std::vector<Field *> Field::createListField(const std::vector<Symbol *> &symbols) {
    std::vector<Field *> listFields;
    Field *tmpField;

    for(auto & symbolList: Statement::splitComa(symbols)) {
        tmpField = convertToField(symbolList);
        listFields.push_back(tmpField);
    }

    return listFields;
}

Field *Field::convertToField(const std::vector<Symbol *> &symbols) {
    std::vector<Symbol *> usableSymbols = symbols;
    bool parenthesis = false;
    Field *field;

    if (symbols.size() > 2 && symbols[0]->symbolValueType == s_Delimiter && ((DelimiterSymbol *) symbols[0])->keyword == v_ParenthesisLeft
        && symbols[symbols.size() - 1]->symbolValueType == s_Delimiter && ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword == v_ParenthesisRight) {
        usableSymbols = Statement::cut_symbol_vector(symbols, 1, symbols.size() - 1);
        parenthesis = true;
    }

    field = tryConvertToColumnReference(usableSymbols);
    if (field == nullptr) {
        field = tryConvertToConst(usableSymbols);
    }
    if (field == nullptr) {
        field = tryConvertToFunction(usableSymbols);
    }
    if (field == nullptr) {
        field = tryConvertToOperation(usableSymbols);
    }
    if (field == nullptr && parenthesis) {
        field = tryConvertToStatement(usableSymbols);
    }

    if (field == nullptr) {
        Error::syntaxError(usableSymbols[0]);
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

    if (symbols.empty() || symbols[0]->symbolValueType != s_Statement) {
        return nullptr;
    }

    return Parser::createStatement(symbols);
}

Field *Field::tryConvertToOperation(const std::vector<Symbol *> &symbols) {
    int parenthesis_count = 0;
    int min_parenthesis_count = -1;
    int min_operator = -1;
    int min_index = -1;
    int tmp_val;

    for (int i = 1; i < symbols.size() - 1; i++) {
        if (parenthesis_count < 0) {
            Error::syntaxError(")");
        }
        if (symbols[i]->symbolValueType == s_Delimiter) {
            if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisLeft) {
                parenthesis_count++;
            } else if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisRight) {
                parenthesis_count--;
            }
            continue;
        }
        if (symbols[i]->symbolValueType == s_Keyword || symbols[i]->symbolValueType == s_Operator) {
            tmp_val = tryConvertToOperatorEnum(symbols[i]);
            if (tmp_val != -1) {
                if (min_index == -1) {
                    min_index = i;
                    min_operator = tmp_val;
                    min_parenthesis_count = parenthesis_count;
                } else {
                    if (min_parenthesis_count > parenthesis_count) {
                        min_index = i;
                        min_operator = tmp_val;
                        min_parenthesis_count = parenthesis_count;
                    } else if (min_parenthesis_count == parenthesis_count && min_operator > tmp_val) {
                        min_index = i;
                        min_operator = tmp_val;
                        min_parenthesis_count = parenthesis_count;
                    }
                }
            }
        }
    }

    if (min_index != -1) {
        return new Operation(
                    convertToField(Statement::cut_symbol_vector(symbols, 0, min_index)),
                    (OperationPriorityEnum) min_operator,
                    convertToField(Statement::cut_symbol_vector(symbols, min_index + 1, symbols.size()))
                );
    }

    return nullptr;
}

int Field::tryConvertToOperatorEnum(Symbol *symbol) {

    if (symbol->symbolValueType == s_Operator) {
        if (((OperatorSymbol*) symbol)->keyword == v_Greater) {
            return o_Greater;
        } else if (((OperatorSymbol*) symbol)->keyword == v_GreaterEqual) {
            return o_GreaterEqual;
        } else if (((OperatorSymbol*) symbol)->keyword == v_Lower) {
            return o_Lower;
        } else if (((OperatorSymbol*) symbol)->keyword == v_LowerEqual) {
            return o_LowerEqual;
        } else if (((OperatorSymbol*) symbol)->keyword == v_NotEqual) {
            return o_NotEqual;
        } else if (((OperatorSymbol*) symbol)->keyword == v_Equal) {
            return o_Equal;
        } else if (((OperatorSymbol*) symbol)->keyword == v_BitAnd) {
            return o_BitAnd;
        } else if (((OperatorSymbol*) symbol)->keyword == v_BitOr) {
            return o_BitOr;
        } else if (((OperatorSymbol*) symbol)->keyword == v_BitXor) {
            return o_BitXor;
        } else if (((OperatorSymbol*) symbol)->keyword == v_Add) {
            return o_Add;
        } else if (((OperatorSymbol*) symbol)->keyword == v_Sub) {
            return o_Sub;
        } else if (((OperatorSymbol*) symbol)->keyword == v_Mul) {
            return o_Mul;
        } else if (((OperatorSymbol*) symbol)->keyword == v_Div) {
            return o_Div;
        } else if (((OperatorSymbol*) symbol)->keyword == v_Modulo) {
            return o_Mod;
        }
    } else if (symbol->symbolValueType == s_Keyword) {
        if (((KeywordSymbol *) symbol)->keyword == k_And) {
            return o_And;
        } else if (((KeywordSymbol *) symbol)->keyword == k_Or) {
            return o_Or;
        } else if (((KeywordSymbol *) symbol)->keyword == k_Not) {
            return o_Not;
        } else if (((KeywordSymbol *) symbol)->keyword == k_In) {
            return o_In;
        } else if (((KeywordSymbol *) symbol)->keyword == k_Between) {
            return o_Between;
        } else if (((KeywordSymbol *) symbol)->keyword == k_Like) {
            return o_Like;
        } else if (((KeywordSymbol *) symbol)->keyword == k_Some) {
            return o_Some;
        } else if (((KeywordSymbol *) symbol)->keyword == k_Exists) {
            return o_Exists;
        }
    }
    return -1;
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

ReturnedValue *ConstNumberField::execute() {
    return nullptr;
}

ReturnedValue *ConstStringField::execute() {
    return nullptr;
}

ReturnedValue *NullField::execute() {
    return nullptr;
}
