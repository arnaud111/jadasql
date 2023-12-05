//
// Created by nono on 12/10/23.
//

#ifndef JADA_NUMBERSYMBOL_H
#define JADA_NUMBERSYMBOL_H

#include "../Symbol.h"

class NumberSymbol : public Symbol {

public:
    int value;

    explicit NumberSymbol(int val) {
        this->symbolValueType = s_Number;
        this->value = val;
    }

    void display() override {
        printf("Number : %d\n", this->value);
    }
};

#endif //JADA_NUMBERSYMBOL_H
