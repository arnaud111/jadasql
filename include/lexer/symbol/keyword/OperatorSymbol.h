//
// Created by nono on 11/10/23.
//

#ifndef JADA_OPERATORSYMBOL_H
#define JADA_OPERATORSYMBOL_H

#include "../Symbol.h"
#include <string>

enum OperatorSymbolEnum {
    v_Greater,
    v_Lower,
    v_GreaterEqual,
    v_LowerEqual,
    v_NotEqual,
    v_NotEqual2,
    v_Equal,
    v_Add,
    v_Sub,
    v_Mul,
    v_Div,
    v_Modulo,
    v_AddEqual,
    v_SubEqual,
    v_MulEqual,
    v_DivEqual,
    v_ModuloEqual,
    v_BitAnd,
    v_BitOr,
    v_BitXor,
    v_BitAndEqual,
    v_BitOrEqual,
    v_BitXorEqual,
};

class OperatorSymbol : public Symbol {

public:
    static int size;
    static std::string stringValues[23];
    OperatorSymbolEnum keyword;

    explicit OperatorSymbol(int val) {
        this->symbolValueType = s_Operator;
        if (val >= v_Greater && val <= v_BitXorEqual) {
            this->keyword = static_cast<OperatorSymbolEnum>(val);
        } else {
            this->keyword = v_Greater;
        }
    }

    void display() override {
        printf("Operator : %s\n", OperatorSymbol::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_OPERATORSYMBOL_H
