//
// Created by nono on 21/11/2023.
//


#include <vector>
#include "ColumnCreationInfo.h"
#include "ColumnDetail.h"
#include "ColumnConstraints.h"

ColumnCreationInfo *ColumnCreationInfo::convertToColumnCreationInfo(std::vector<Symbol *> symbols) {
    if (symbols[0]->symbolValueType == s_Identifier) {
        return new ColumnDetail(symbols);
    }
    return ColumnConstraints::convertToColumnConstraints(symbols);
}

