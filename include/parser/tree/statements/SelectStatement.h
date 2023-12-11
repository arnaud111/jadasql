//
// Created by nono on 10/10/23.
//

#ifndef JADA_SELECTSTATEMENT_H
#define JADA_SELECTSTATEMENT_H

#include <vector>
#include <string>
#include "Statement.h"
#include "../field/Field.h"
#include "../from/From.h"
#include "../operation/Operation.h"
#include "../../../lexer/symbol/Symbol.h"


class SelectStatement : public Statement {

public:
    std::vector<Field *> field;
    From *from;
    Field * where;
    std::vector<Field *> groupBy;
    std::vector<Field *> orderBy;
    bool asc;
    int limit;
    bool distinct;

    explicit SelectStatement(const std::vector<Symbol *> &symbols);

    void display() override;

    ReturnedValue *execute() override;

private:
    static bool isDistinct(std::vector<Symbol *> symbols);
};


#endif //JADA_SELECTSTATEMENT_H
