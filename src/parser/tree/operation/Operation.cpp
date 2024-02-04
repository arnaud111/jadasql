//
// Created by nono on 13/11/2023.
//

#include "parser/tree/operation/Operation.h"
#include "parser/tree/field/ConstStringField.h"
#include "parser/tree/field/ConstNumberField.h"
#include "parser/tree/structure/ColumnReference.h"
#include "error/Error.h"
#include "interpreter/values/ReturnedString.h"
#include "interpreter/values/ReturnedBool.h"
#include "interpreter/values/ReturnedNumber.h"

Operation::Operation(Field *field1, OperationPriorityEnum operation, Field *field2) {
    this->field1 = field1;
    this->operation = operation;
    this->field2 = field2;
    this->fieldType = f_Operation;
}

ReturnedValue *Operation::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Operation::executeWhere(std::vector<Field *> row, std::vector<std::string> columnName) {

    ReturnedValue *field1Value = nullptr;
    ReturnedValue *field2Value = nullptr;

    if (this->field1->fieldType == f_Operation) {
        field1Value = ((Operation *) this->field1)->executeWhere(row, columnName);
    } else if (this->field1->fieldType == f_Column) {
        field1Value = ((ColumnReference *) this->field1)->execute(row, columnName);
    } else if (this->field1->fieldType == f_ConstString) {
        field1Value = ((ConstStringField *) this->field1)->execute();
    } else if (this->field1->fieldType == f_ConstNumber) {
        field1Value = ((ConstNumberField *) this->field1)->execute();
    }

    if (this->field2->fieldType == f_Operation) {
        field2Value = ((Operation *) this->field2)->executeWhere(row, columnName);
    } else if (this->field2->fieldType == f_Column) {
        field2Value = ((ColumnReference *) this->field2)->execute(row, columnName);
    } else if (this->field2->fieldType == f_ConstString) {
        field2Value = ((ConstStringField *) this->field2)->execute();
    } else if (this->field2->fieldType == f_ConstNumber) {
        field2Value = ((ConstNumberField *) this->field2)->execute();
    }

    if (field1Value == nullptr || field2Value == nullptr) {
        Error::runtimeError("Not implemented");
    }

    return this->executeOperation(field1Value, field2Value);
}

ReturnedValue *Operation::executeOperation(ReturnedValue *field1, ReturnedValue *field2) {
    switch (this->operation) {
        case o_Or:
            return Operation::executeOr(field1, field2);
        case o_And:
            return Operation::executeAnd(field1, field2);
        case o_Not:
            return Operation::executeNot(field1, field2);
        case o_In:
            return Operation::executeIn(field1, field2);
        case o_Between:
            return Operation::executeBetween(field1, field2);
        case o_Like:
            return Operation::executeLike(field1, field2);
        case o_Some:
            return Operation::executeSome(field1, field2);
        case o_Exists:
            return Operation::executeExists(field1, field2);
        case o_Greater:
            return Operation::executeGreater(field1, field2);
        case o_GreaterEqual:
            return Operation::executeGreaterEqual(field1, field2);
        case o_Lower:
            return Operation::executeLower(field1, field2);
        case o_LowerEqual:
            return Operation::executeLowerEqual(field1, field2);
        case o_NotEqual:
            return Operation::executeNotEqual(field1, field2);
        case o_Equal:
            return Operation::executeEqual(field1, field2);
        case o_BitAnd:
            return Operation::executeBitAnd(field1, field2);
        case o_BitOr:
            return Operation::executeBitOr(field1, field2);
        case o_BitXor:
            return Operation::executeBitXor(field1, field2);
        case o_Add:
            return Operation::executeAdd(field1, field2);
        case o_Sub:
            return Operation::executeSub(field1, field2);
        case o_Mul:
            return Operation::executeMul(field1, field2);
        case o_Div:
            return Operation::executeDiv(field1, field2);
        case o_Mod:
            return Operation::executeMod(field1, field2);
    }
    return nullptr;
}

ReturnedValue *Operation::executeOr(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeAnd(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeNot(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeIn(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeBetween(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeLike(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeSome(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeExists(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeGreater(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeGreaterEqual(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeLower(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeLowerEqual(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeNotEqual(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeEqual(ReturnedValue *field1, ReturnedValue *field2) {

    if (field1->type != field2->type) {
        return nullptr;
    }

    if (field1->type == String) {
        return new ReturnedBool(((ReturnedString *) field1)->value == ((ReturnedString *) field2)->value);
    } else if (field1->type == Number) {
        return new ReturnedBool(((ReturnedNumber *) field1)->value == ((ReturnedNumber *) field2)->value);
    }

    return nullptr;
}

ReturnedValue *Operation::executeBitAnd(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeBitOr(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeBitXor(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeAdd(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeSub(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeMul(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeDiv(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}

ReturnedValue *Operation::executeMod(ReturnedValue *field1, ReturnedValue *field2) {
    return nullptr;
}
