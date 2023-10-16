//
// Created by nono on 11/10/23.
//

#ifndef JADA_STATEMENTSYMBOL_H
#define JADA_STATEMENTSYMBOL_H

#include "../Symbol.h"
#include <string>

enum StatementSymbolEnum {
    v_Select,
    v_Update,
    v_Delete,
    v_Drop,
    v_Insert,
    v_Create,
    v_Alter,
};

class StatementSymbol: public Symbol {

public:
    static int size;
    static std::string stringValues[7];
    StatementSymbolEnum keyword;

    explicit StatementSymbol(int val) {
        this->symbolValueType = s_Statement;
        if (val >= v_Select && val <= v_Alter) {
            this->keyword = static_cast<StatementSymbolEnum>(val);
        } else {
            this->keyword = v_Select;
        }
    }

    void display() override {
        printf("Statement : %s\n", StatementSymbol::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_STATEMENTSYMBOL_H
