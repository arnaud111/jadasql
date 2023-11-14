//
// Created by nono on 13/11/2023.
//

#ifndef JADA_CREATESTATEMENT_H
#define JADA_CREATESTATEMENT_H


#include "Statement.h"
#include "../column_actions/ColumnDetail.h"

enum CreateStatementTypeEnum {
    CreateTable,
    CreateDatabase,
};

class CreateStatement : public Statement {

public:
    CreateStatementTypeEnum type;
    bool ifExist;
    Field *createdField;
    std::vector<ColumnDetail *> columns;

};


#endif //JADA_CREATESTATEMENT_H
