//
// Created by nono on 12/12/23.
//

#ifndef JADA_SHOWSTATEMENT_H
#define JADA_SHOWSTATEMENT_H

#include <vector>
#include "lexer/symbol/Symbol.h"
#include "Statement.h"

enum ShowTypes {
    ShowDatabases,
    ShowTables,
};

class ShowStatement: public Statement {

public:
    ShowTypes type;

    explicit ShowStatement(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue * execute() override;
};

#endif //JADA_SHOWSTATEMENT_H
