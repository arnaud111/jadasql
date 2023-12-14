//
// Created by nono on 13/11/2023.
//

#ifndef JADA_DELETESTATEMENT_H
#define JADA_DELETESTATEMENT_H


#include "Statement.h"
#include "../structure/TableReference.h"

class DeleteStatement : public Statement {

public:
    TableReference *table;
    Field * where;

    explicit DeleteStatement(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};


#endif //JADA_DELETESTATEMENT_H
