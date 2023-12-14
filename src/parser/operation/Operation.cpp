//
// Created by nono on 13/11/2023.
//

#include "../../../include/parser/tree/operation/Operation.h"

Operation::Operation(Field *field1, OperationPriorityEnum operation, Field *field2) {
    this->field1 = field1;
    this->operation = operation;
    this->field2 = field2;
    this->fieldType = f_Operation;
}

ReturnedValue *Operation::execute(ExecutionData *executionData) {
    return nullptr;
}
