//
// Created by nono on 12/10/23.
//

#ifndef JADA_NUMBERSYMBOLVALUE_H
#define JADA_NUMBERSYMBOLVALUE_H

#include "SymbolValue.h"

class NumberSymbolValue: public SymbolValue {

public:
    int value;

    explicit NumberSymbolValue(int val) {
        this->symbolValueType = v_Number;
        this->value = val;
    }

    void display() override {
        printf("g_Number : %d", this->value);
    }
};

#endif //JADA_NUMBERSYMBOLVALUE_H
