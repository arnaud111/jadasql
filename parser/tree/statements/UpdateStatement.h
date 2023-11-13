//
// Created by nono on 13/11/2023.
//

#ifndef JADA_UPDATESTATEMENT_H
#define JADA_UPDATESTATEMENT_H


#include "Statement.h"
#include "../structure/TableReference.h"

class UpdateStatement : public Statement {

public:
    TableReference *tableReference;
    std::vector<Field *> set;
    Field * where;
};


#endif //JADA_UPDATESTATEMENT_H
