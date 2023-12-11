//
// Created by nono on 10/10/23.
//

#ifndef JADA_OPERATION_H
#define JADA_OPERATION_H

#include <vector>
#include <cstdio>
#include "../../../lexer/symbol/Symbol.h"
#include "../field/Field.h"
#include "OperationPriority.h"

class Operation : public Field {

public:
    Field *field1;
    OperationPriorityEnum operation;
    Field *field2;

    explicit Operation(Field *field1, OperationPriorityEnum operation, Field *field2);

    void display() override;

    ReturnedValue *execute() override;
};

#endif //JADA_OPERATION_H
