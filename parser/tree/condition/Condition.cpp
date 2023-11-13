//
// Created by nono on 13/11/2023.
//

#include "Condition.h"

Condition::Condition(Field *field1, OperationPriorityEnum operation, Field *field2) {
    this->field1 = field1;
    this->operation = operation;
    this->field2 = field2;
}