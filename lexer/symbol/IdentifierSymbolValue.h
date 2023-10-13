//
// Created by nono on 13/10/23.
//

#ifndef JADA_IDENTIFIERSYMBOLVALUE_H
#define JADA_IDENTIFIERSYMBOLVALUE_H

#include <string>
#include <utility>
#include "SymbolValue.h"

class IdentifierSymbolValue: public SymbolValue {

public:
    std::string value;

    explicit IdentifierSymbolValue(std::string val) {
        this->symbolValueType = v_Identifier;
        this->value = std::move(val);
    }

    void display() override {
        printf("Identifier : %s\n", this->value.c_str());
    }
};

#endif //JADA_IDENTIFIERSYMBOLVALUE_H
