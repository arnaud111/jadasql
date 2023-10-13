//
// Created by nono on 11/10/23.
//

#ifndef JADA_STATEMENTKEYWORD_H
#define JADA_STATEMENTKEYWORD_H

#include "../SymbolValue.h"
#include <string>

enum StatementKeywordEnum {
    Select,
    Update,
    Delete,
    Drop,
    Insert,
    Create,
    Alter,
};

class StatementKeyword: public SymbolValue {

public:
    static int size;
    static std::string stringValues[7];
    StatementKeywordEnum keyword;

    explicit StatementKeyword(int val) {
        this->symbolValueType = v_Statement;
        if (val >= Select && val <= Alter) {
            this->keyword = static_cast<StatementKeywordEnum>(val);
        } else {
            this->keyword = Select;
        }
    }

    void display() override {
        printf("Statement : %s", StatementKeyword::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_STATEMENTKEYWORD_H
