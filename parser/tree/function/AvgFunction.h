//
// Created by nono on 17/10/2023.
//

#ifndef JADA_AVGFUNCTION_H
#define JADA_AVGFUNCTION_H

#include <vector>
#include "Function.h"
#include "../expression/Expression.h"

class AvgFunction : public Function {

public:

    Field *field;

    explicit AvgFunction(Field *field) {
        this->function = f_Avg;
        this->field = field;
    };

    void display() override;
};

#endif //JADA_AVGFUNCTION_H
