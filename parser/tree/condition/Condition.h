//
// Created by nono on 10/10/23.
//

#ifndef JADA_CONDITION_H
#define JADA_CONDITION_H

#include <vector>
#include "LogicalKeyword.h"
#include "../expression/Expression.h"
#include "../../../lexer/symbol/Symbol.h"

class Condition: public Expression {
    Expression *expression1;
    LogicalKeyword *logicalKeyword;
    Expression *expression2;

    bool evaluate() override {
        return true;
    }

public:
    explicit Condition(const std::vector<Symbol *>& symbols);
};

#endif //JADA_CONDITION_H
