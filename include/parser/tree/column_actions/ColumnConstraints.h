//
// Created by nono on 14/11/2023.
//

#ifndef JADA_COLUMNCONSTRAINTS_H
#define JADA_COLUMNCONSTRAINTS_H

#include <vector>
#include "ColumnCreationInfo.h"
#include "../../../lexer/symbol/Symbol.h"

enum ColumnConstrainsType {
    c_Check,
    c_Unique,
    c_PrimaryKey,
    c_ForeignKey,
};

class ColumnConstraints: public ColumnCreationInfo {

public:

    ColumnConstrainsType columnConstrainsType;

    static ColumnConstraints *convertToColumnConstraints(std::vector<Symbol *> symbols);
};


#endif //JADA_COLUMNCONSTRAINTS_H
