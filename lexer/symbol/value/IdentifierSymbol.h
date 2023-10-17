//
// Created by nono on 13/10/23.
//

#ifndef JADA_IDENTIFIERSYMBOL_H
#define JADA_IDENTIFIERSYMBOL_H

#include <string>
#include <utility>
#include "../Symbol.h"

class IdentifierSymbol : public Symbol {

public:
    std::string value;

    explicit IdentifierSymbol(std::string val) {
        this->symbolValueType = s_Identifier;
        this->value = std::move(val);
    }

    void display() override {
        printf("Identifier : %s\n", this->value.c_str());
    }
};

#endif //JADA_IDENTIFIERSYMBOL_H
