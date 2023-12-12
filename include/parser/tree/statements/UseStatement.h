//
// Created by nono on 12/12/23.
//

#ifndef JADA_USESTATEMENT_H
#define JADA_USESTATEMENT_H

#include <vector>
#include "lexer/symbol/Symbol.h"
#include "Statement.h"
#include "parser/tree/structure/DatabaseReference.h"

class UseStatement : public Statement {

public:

    DatabaseReference *database;

    explicit UseStatement(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue * execute() override;

};

#endif //JADA_USESTATEMENT_H
