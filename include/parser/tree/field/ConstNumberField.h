//
// Created by nono on 17/10/2023.
//

#ifndef JADA_CONSTNUMBERFIELD_H
#define JADA_CONSTNUMBERFIELD_H

#include "Field.h"

class ConstNumberField: public Field {

public:

    int value;

    explicit ConstNumberField(int value) {
        this->value = value;
        this->fieldType = f_ConstNumber;
    }

    void display() override;
};

#endif //JADA_CONSTNUMBERFIELD_H
