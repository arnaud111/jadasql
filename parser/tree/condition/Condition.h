//
// Created by nono on 10/10/23.
//

#ifndef JADA_CONDITION_H
#define JADA_CONDITION_H

#include <vector>
#include <cstdio>
#include "LogicalKeyword.h"
#include "../expression/Expression.h"
#include "../../../lexer/symbol/Symbol.h"

class Condition : public Expression {

public:
    Expression *expression1;
    LogicalKeyword *logicalKeyword;
    Expression *expression2;

    bool evaluate() override {
        return true;
    }

    explicit Condition(const std::vector<Symbol *> &symbols);

    void display() override;
};

#endif //JADA_CONDITION_H
