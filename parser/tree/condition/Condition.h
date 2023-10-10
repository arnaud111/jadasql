//
// Created by nono on 10/10/23.
//

#ifndef JADA_CONDITION_H
#define JADA_CONDITION_H

#include "LogicalKeyword.h"
#include "../expression/Expression.h"

class Condition: public Expression {
    Expression *expression1;
    LogicalKeyword *logicalKeyword;
    Expression *expression2;

    Condition() {
        expression1 = nullptr;
        logicalKeyword = nullptr;
        expression2 = nullptr;
    }

    explicit Condition(Expression *expression) {
        expression1 = expression;
        logicalKeyword = nullptr;
        expression2 = nullptr;
    }

    explicit Condition(Expression *expression1, LogicalKeyword *logicalKeyword, Expression *expression2) {
        this->expression1 = expression1;
        this->logicalKeyword = logicalKeyword;
        this->expression2 = expression2;
    }

    bool evaluate() override {
        return true;
    }
};

#endif //JADA_CONDITION_H
