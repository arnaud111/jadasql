//
// Created by a833444 on 17/10/2023.
//

#include "FunctionField.h"

FunctionField::FunctionField()  {
    this->function = f_Left;
}

FunctionField::FunctionField(int val) {
    this->fieldType = f_Function;
    if (val >= f_Left && val <= f_Coalesce) {
        this->function = (FunctionEnum) val;
    } else {
        this->function = f_Left;
    }
}

int FunctionField::tryConvertToFunctionEnum(KeywordSymbolEnum keywordSymbolEnum) {
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

FunctionField *FunctionField::tryConvertToFunctionField(const std::vector<Symbol *> &symbols, FunctionEnum function) {
    std::vector<Symbol *> listSymbolInArgument;
    std::vector<Field *> listField;

    for (int i = 2; i < symbols.size() - 1; i++) {
        listSymbolInArgument.push_back(symbols[i]);
    }

    listField = Field::createListField(listSymbolInArgument);

    switch (function) {
        case f_Left:
            if (listField.size() != 2) return nullptr;
            //return new LeftFunction(listField[0], listField[1]);
            break;
        case f_Right:
            if (listField.size() != 2) return nullptr;
            break;
        case f_Max:
            if (listField.size() != 1) return nullptr;
            break;
        case f_Min:
            if (listField.size() != 1) return nullptr;
            break;
        case f_Sum:
            if (listField.size() != 1) return nullptr;
            break;
        case f_Count:
            if (listField.size() != 1) return nullptr;
            break;
        case f_Concat:
            break;
        case f_Format:
            if (listField.size() != 2) return nullptr;
            break;
        case f_Avg:
            if (listField.size() != 1) return nullptr;
            break;
        case f_IfNull:
            if (listField.size() != 2) return nullptr;
            break;
        case f_Coalesce:
            break;
    }

    return nullptr;
}
