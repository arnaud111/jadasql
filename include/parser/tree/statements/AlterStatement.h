//
// Created by nono on 13/11/2023.
//

#ifndef JADA_ALTERSTATEMENT_H
#define JADA_ALTERSTATEMENT_H


#include "Statement.h"
#include "../structure/TableReference.h"
#include "../column_actions/ColumnModification.h"

class AlterStatement : public Statement {

public:
    TableReference *table;
    std::vector<ColumnModification *> modifications;

    explicit AlterStatement(std::vector<Symbol *> symbols);

    void display() override;

};


#endif //JADA_ALTERSTATEMENT_H
