//
// Created by a833444 on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include "FunctionField.h"
#include "../expression/Expression.h"

class LeftFunction : public FunctionField {

public:

    Field *field1;
    Field *field2;

    explicit LeftFunction(Field *field1, Field *field2) {
        this->function = f_Left;
        this->field1 = field1;
        this->field2 = field2;
    };
};

#endif //JADA_LEFTFUNCTION_H
