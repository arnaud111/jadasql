//
// Created by nono on 17/10/2023.
//

#ifndef JADA_FUNCTION_H
#define JADA_FUNCTION_H

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

class Function : public Field {

public:

    FunctionEnum function;

    explicit Function();

    explicit Function(int val);

    static int tryConvertToFunctionEnum(KeywordSymbolEnum keywordSymbolEnum);
};

#endif //JADA_FUNCTION_H
