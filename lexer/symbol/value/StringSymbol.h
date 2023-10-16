//
// Created by nono on 11/10/23.
//

#ifndef JADA_STRINGSYMBOL_H
#define JADA_STRINGSYMBOL_H

#include <string>
#include <utility>
#include "../Symbol.h"

class StringSymbol: public Symbol {

public:
    std::string value;

    explicit StringSymbol(std::string val) {
        this->symbolValueType = s_String;
        this->value = std::move(val);
    }

    void display() override {
        printf("String : %s\n", this->value.c_str());
    }
};

#endif //JADA_STRINGSYMBOL_H
