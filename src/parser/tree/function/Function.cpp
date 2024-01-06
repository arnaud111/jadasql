//
// Created by nono on 17/10/2023.
//

#include "parser/tree/function/Function.h"
#include "parser/tree/function/AvgFunction.h"
#include "parser/tree/function/CoalesceFunction.h"
#include "parser/tree/function/ConcatFunction.h"
#include "parser/tree/function/CountFunction.h"
#include "parser/tree/function/FormatFunction.h"
#include "parser/tree/function/IfNullFunction.h"
#include "parser/tree/function/LeftFunction.h"
#include "parser/tree/function/RightFunction.h"
#include "parser/tree/function/MaxFunction.h"
#include "parser/tree/function/MinFunction.h"
#include "parser/tree/function/SumFunction.h"

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

ReturnedValue *AvgFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *CoalesceFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *ConcatFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *CountFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *FormatFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *IfNullFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *LeftFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *RightFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *MaxFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *MinFunction::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *SumFunction::execute(ExecutionData *executionData) {
    return nullptr;
}
