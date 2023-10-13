//
// Created by nono on 11/10/23.
//

#ifndef JADA_STRINGSYMBOLVALUE_H
#define JADA_STRINGSYMBOLVALUE_H

#include <string>
#include <utility>
#include "SymbolValue.h"

class StringSymbolValue: public SymbolValue {

public:
    std::string value;

    explicit StringSymbolValue(std::string val) {
        this->symbolValueType = v_String;
        this->value = std::move(val);
    }

    void display() override {
        printf("g_String : %s", this->value.c_str());
    }
};

#endif //JADA_STRINGSYMBOLVALUE_H
