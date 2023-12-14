//
// Created by nono on 17/10/2023.
//

#ifndef JADA_COUNTFUNCTION_H
#define JADA_COUNTFUNCTION_H

#include "Function.h"

class CountFunction : public Function {

public:

    Field *field;

    explicit CountFunction(Field *field) {
        this->function = f_Count;
        this->field = field;
    };

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_COUNTFUNCTION_H
