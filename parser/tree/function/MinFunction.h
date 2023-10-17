//
// Created by a833444 on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include "FunctionField.h"
#include "../expression/Expression.h"

class MinFunction : public FunctionField {

public:

    Field *field;

    explicit MinFunction(Field *field) {
        this->function = f_Min;
        this->field = field;
    };
};

#endif //JADA_LEFTFUNCTION_H
