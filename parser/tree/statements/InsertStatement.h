//
// Created by nono on 13/11/2023.
//

#ifndef JADA_INSERTSTATEMENT_H
#define JADA_INSERTSTATEMENT_H


#include "Statement.h"
#include "../structure/TableReference.h"
#include "../structure/ColumnReference.h"

class InsertStatement : public Statement {

public:
    TableReference *tableReference;
    std::vector<ColumnReference*> columns;
    std::vector<Field *> values;
};


#endif //JADA_INSERTSTATEMENT_H
