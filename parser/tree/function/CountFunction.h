//
// Created by a833444 on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include "FunctionField.h"
#include "../expression/Expression.h"

class CountFunction : public FunctionField {

public:

    Field *field;

    explicit CountFunction(Field *field) {
        this->function = f_Count;
        this->field = field;
    };
};

#endif //JADA_LEFTFUNCTION_H
