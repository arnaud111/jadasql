//
// Created by nono on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include "Function.h"

class LeftFunction : public Function {

public:

    Field *field1;
    Field *field2;

    explicit LeftFunction(Field *field1, Field *field2) {
        this->function = f_Left;
        this->field1 = field1;
        this->field2 = field2;
    };

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_LEFTFUNCTION_H
