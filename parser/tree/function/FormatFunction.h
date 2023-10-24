//
// Created by nono on 17/10/2023.
//

#ifndef JADA_FORMATFUNCTION_H
#define JADA_FORMATFUNCTION_H

#include "Function.h"

class FormatFunction : public Function {

public:

    Field *field1;
    Field *field2;

    explicit FormatFunction(Field *field1, Field *field2) {
        this->function = f_Format;
        this->field1 = field1;
        this->field2 = field2;
    };

    void display() override;
};

#endif //JADA_FORMATFUNCTION_H
