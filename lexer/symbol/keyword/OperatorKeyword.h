//
// Created by nono on 11/10/23.
//

#ifndef JADA_OPERATORKEYWORD_H
#define JADA_OPERATORKEYWORD_H

#include "../SymbolValue.h"
#include <string>

enum OperatorKeywordEnum {
    Greater,
    Less,
    GreaterEqual,
    LessEqual,
    EqualEqual,
    NotEqual,
    NotEqual2,
    Equal,
    Add,
    Sub,
    Mul,
    Div,
    Modulo,
    AddEqual,
    SubEqual,
    MulEqual,
    DivEqual,
    ModuloEqual,
    BitAnd,
    BitOr,
    BitXor,
    BitAndEqual,
    BitOrEqual,
    BitXorEqual,
};

class OperatorKeyword: public SymbolValue {

public:
    static int size;
    static std::string stringValues[24];
    OperatorKeywordEnum keyword;

    explicit OperatorKeyword(int val) {
        this->symbolValueType = v_Operator;
        if (val >= Greater && val <= BitXorEqual) {
            this->keyword = static_cast<OperatorKeywordEnum>(val);
        } else {
            this->keyword = Greater;
        }
    }

    void display() override {
        printf("g_Operator : %s", OperatorKeyword::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_OPERATORKEYWORD_H
