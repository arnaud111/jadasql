//
// Created by nono on 17/10/2023.
//

#ifndef JADA_MINFUNCTION_H
#define JADA_MINFUNCTION_H

#include "Function.h"

class MinFunction : public Function {

public:

    Field *field;

    explicit MinFunction(Field *field) {
        this->function = f_Min;
        this->field = field;
    };

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_MINFUNCTION_H
