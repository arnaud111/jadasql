//
// Created by nono on 21/11/2023.
//


#include <vector>
#include "../../../include/parser/tree/column_actions/ColumnCreationInfo.h"
#include "../../../include/parser/tree/column_actions/ColumnDetail.h"
#include "../../../include/parser/tree/column_actions/ColumnConstraints.h"

ColumnCreationInfo *ColumnCreationInfo::convertToColumnCreationInfo(std::vector<Symbol *> symbols) {
    if (symbols[0]->symbolValueType == s_Identifier) {
        return new ColumnDetail(symbols);
    }
    return ColumnConstraints::convertToColumnConstraints(symbols);
}

