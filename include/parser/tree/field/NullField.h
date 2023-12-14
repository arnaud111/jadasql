//
// Created by nono on 21/11/2023.
//

#ifndef JADA_NULLFIELD_H
#define JADA_NULLFIELD_H

#include "Field.h"

class NullField: public Field {

public:

    explicit NullField() {
        this->fieldType = f_Null;
    }

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_NULLFIELD_H
