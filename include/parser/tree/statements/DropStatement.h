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

private:

    static DropStatementTypeEnum getDropType(Symbol *symbol);
};


#endif //JADA_DROPSTATEMENT_H
