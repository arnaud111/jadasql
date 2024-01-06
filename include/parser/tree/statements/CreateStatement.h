//
// Created by nono on 13/11/2023.
//

#ifndef JADA_CREATESTATEMENT_H
#define JADA_CREATESTATEMENT_H


#include "Statement.h"
#include "../column_actions/ColumnCreationInfo.h"

enum CreateStatementTypeEnum {
    CreateTable,
    CreateDatabase,
};

class CreateStatement : public Statement {

public:
    CreateStatementTypeEnum type;
    bool ifNotExist;
    Field *createdField;
    std::vector<ColumnCreationInfo *> columns;

    explicit CreateStatement(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

private:

    void createDatabase(std::vector<Symbol *> symbols);

    void createTable(std::vector<Symbol *> symbols);

    ReturnedValue *executeCreateDatabase(ExecutionData *executionData) const;

    ReturnedValue *executeCreateTable(ExecutionData *executionData) const;
};


#endif //JADA_CREATESTATEMENT_H
