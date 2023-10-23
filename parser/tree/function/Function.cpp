//
// Created by nono on 17/10/2023.
//

#include "Function.h"

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
        case v_Left:
            return f_Left;
        case v_Right:
            return f_Right;
        case v_Max:
            return f_Max;
        case v_Sum:
            return f_Sum;
        case v_Count:
            return f_Count;
        case v_Concat:
            return f_Concat;
        case v_Format:
            return f_Format;
        case v_Min:
            return f_Min;
        case v_Avg:
            return f_Avg;
        case v_IfNull:
            return f_IfNull;
        case v_Coalesce:
            return f_Coalesce;
        default:
            return -1;
    }
}
