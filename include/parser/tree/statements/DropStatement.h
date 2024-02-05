//
// Created by nono on 13/11/2023.
//

#ifndef JADA_DROPSTATEMENT_H
#define JADA_DROPSTATEMENT_H


#include "Statement.h"

enum DropStatementTypeEnum {
    DropTable,
    DropDatabase
};

class DropStatement : public Statement {

public:
    DropStatementTypeEnum type;
    Field* droppedField{};
    bool ifExist;

    explicit DropStatement(const std::vector<Symbol *> &symbols);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

private:

    static DropStatementTypeEnum getDropType(Symbol *symbol);

    ReturnedValue *executeDropTable(ExecutionData *executionData);

    ReturnedValue *executeDropDatabase(ExecutionData *executionData);
};


#endif //JADA_DROPSTATEMENT_H
