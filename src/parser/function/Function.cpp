//
// Created by nono on 17/10/2023.
//

#include "../../../include/parser/tree/function/Function.h"

Function::Function()  {
    this->function = f_Left;
}

Function::Function(int val) {
    this->fieldType = f_Function;
    if (val >= f_Left && val <= f_Coalesce) {
        this->function = (FunctionEnum) val;
    } else {
        this->function = f_Left;
    }
}

int Function::tryConvertToFunctionEnum(KeywordSymbolEnum keywordSymbolEnum) {
    switch (keywordSymbolEnum) {
        case k_Left:
            return f_Left;
        case k_Right:
            return f_Right;
        case k_Max:
            return f_Max;
        case k_Sum:
            return f_Sum;
        case k_Count:
            return f_Count;
        case k_Concat:
            return f_Concat;
        case k_Format:
            return f_Format;
        case k_Min:
            return f_Min;
        case k_Avg:
            return f_Avg;
        case k_IfNull:
            return f_IfNull;
        case k_Coalesce:
            return f_Coalesce;
        default:
            return -1;
    }
}
