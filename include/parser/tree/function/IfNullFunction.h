//
// Created by nono on 17/10/2023.
//

#ifndef JADA_IFNULLFUNCTION_H
#define JADA_IFNULLFUNCTION_H

#include <vector>
#include "Function.h"

class IfNullFunction : public Function {

public:

    Field *field1;
    Field *field2;

    explicit IfNullFunction(Field *field1, Field *field2) {
        this->function = f_IfNull;
        this->field1 = field1;
        this->field2 = field2;
    };

    void display() override;
};

#endif //JADA_IFNULLFUNCTION_H
