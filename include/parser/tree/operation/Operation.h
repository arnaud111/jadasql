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

    ReturnedValue *execute(ExecutionData *executionData) override;

    ReturnedValue *executeWhere(std::vector<Field *> row, std::vector<std::string> columnName);

    ReturnedValue *executeOperation(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeOr(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeAnd(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeNot(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeIn(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeBetween(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeLike(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeSome(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeExists(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeGreater(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeGreaterEqual(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeLower(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeLowerEqual(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeNotEqual(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeEqual(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeBitAnd(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeBitOr(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeBitXor(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeAdd(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeSub(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeMul(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeDiv(ReturnedValue *field1, ReturnedValue *field2);

    static ReturnedValue *executeMod(ReturnedValue *field1, ReturnedValue *field2);
};

#endif //JADA_OPERATION_H
