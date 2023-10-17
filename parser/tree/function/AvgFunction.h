//
// Created by a833444 on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include <vector>
#include "FunctionField.h"
#include "../expression/Expression.h"

class AvgFunction : public FunctionField {

public:

    Field *field;

    explicit AvgFunction(Field *field) {
        this->function = f_Avg;
        this->field = field;
    };
};

#endif //JADA_LEFTFUNCTION_H
