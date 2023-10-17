//
// Created by a833444 on 17/10/2023.
//

#ifndef JADA_FUNCTIONFIELD_H
#define JADA_FUNCTIONFIELD_H

#include <vector>
#include "../field/Field.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"

enum FunctionEnum {
    f_Left,
    f_Right,
    f_Max,
    f_Min,
    f_Sum,
    f_Count,
    f_Concat,
    f_Format,
    f_Avg,
    f_IfNull,
    f_Coalesce,
};

class FunctionField : public Field {

public:

    FunctionEnum function;

    explicit FunctionField();

    explicit FunctionField(int val);

    static int tryConvertToFunctionEnum(KeywordSymbolEnum keywordSymbolEnum);

    static FunctionField *tryConvertToFunctionField(const std::vector<Symbol *> &symbols, FunctionEnum function);

    void display() override;
};

#endif //JADA_FUNCTIONFIELD_H
