//
// Created by nono on 17/10/2023.
//

#ifndef JADA_MINFUNCTION_H
#define JADA_MINFUNCTION_H

#include "Function.h"
#include "../expression/Expression.h"

class MinFunction : public Function {

public:

    Field *field;

    explicit MinFunction(Field *field) {
        this->function = f_Min;
        this->field = field;
    };

    void display() override;
};

#endif //JADA_MINFUNCTION_H
