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
    bool columnsExplicit;
    std::vector<ColumnReference*> columns;
    std::vector<std::vector<Field *>> values;

    explicit InsertStatement(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

private:

    static std::vector<Symbol *> getInParenthesis(unsigned long long start, std::vector<Symbol *> symbols);

};


#endif //JADA_INSERTSTATEMENT_H
