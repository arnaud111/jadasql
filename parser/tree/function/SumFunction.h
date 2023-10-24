//
// Created by nono on 17/10/2023.
//

#ifndef JADA_SUMFUNCTION_H
#define JADA_SUMFUNCTION_H

#include "Function.h"

class SumFunction : public Function {

public:

    Field *field;

    explicit SumFunction(Field *field) {
        this->function = f_Sum;
        this->field = field;
    };

    void display() override;
};

#endif //JADA_SUMFUNCTION_H
