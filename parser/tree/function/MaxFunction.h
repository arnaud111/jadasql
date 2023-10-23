//
// Created by nono on 17/10/2023.
//

#ifndef JADA_MAXFUNCTION_H
#define JADA_MAXFUNCTION_H

#include "Function.h"
#include "../expression/Expression.h"

class MaxFunction : public Function {

public:

    Field *field;

    explicit MaxFunction(Field *field) {
        this->function = f_Max;
        this->field = field;
    };

    void display() override;
};

#endif //JADA_MAXFUNCTION_H
