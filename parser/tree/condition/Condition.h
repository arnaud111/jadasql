//
// Created by nono on 10/10/23.
//

#ifndef JADA_CONDITION_H
#define JADA_CONDITION_H

#include <vector>
#include <cstdio>
#include "../../../lexer/symbol/Symbol.h"
#include "../field/Field.h"
#include "OperationPriority.h"

class Condition : public Field {

public:
    Field *field1;
    OperationPriorityEnum operation;
    Field *field2;

    explicit Condition(Field *field1, OperationPriorityEnum operation, Field *field2);

    void display() override;
};

#endif //JADA_CONDITION_H
