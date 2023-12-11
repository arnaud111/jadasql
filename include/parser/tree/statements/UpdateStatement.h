//
// Created by nono on 13/11/2023.
//

#ifndef JADA_UPDATESTATEMENT_H
#define JADA_UPDATESTATEMENT_H


#include "Statement.h"
#include "../structure/TableReference.h"
#include "../assign/Assign.h"

class UpdateStatement : public Statement {

public:
    TableReference *tableReference;
    std::vector<Assign *> set;
    Field * where;

    explicit UpdateStatement(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue *execute() override;
};


#endif //JADA_UPDATESTATEMENT_H
