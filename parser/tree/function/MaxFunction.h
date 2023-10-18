//
// Created by nono on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include "FunctionField.h"
#include "../expression/Expression.h"

class MaxFunction : public FunctionField {

public:

    Field *field;

    explicit MaxFunction(Field *field) {
        this->function = f_Max;
        this->field = field;
    };
};

#endif //JADA_LEFTFUNCTION_H
