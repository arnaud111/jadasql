//
// Created by nono on 17/10/2023.
//

#ifndef JADA_RIGHTFUNCTION_H
#define JADA_RIGHTFUNCTION_H

#include "Function.h"

class RightFunction : public Function {

public:

    Field *field1;
    Field *field2;

    explicit RightFunction(Field *field1, Field *field2) {
        this->function = f_Right;
        this->field1 = field1;
        this->field2 = field2;
    };

    void display() override;

    ReturnedValue *execute() override;
};

#endif //JADA_RIGHTFUNCTION_H
