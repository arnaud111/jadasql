//
// Created by nono on 11/10/23.
//

#ifndef JADA_DELIMITERSYMBOL_H
#define JADA_DELIMITERSYMBOL_H

#include "../Symbol.h"
#include <string>

enum DelimiterSymbolEnum {
    v_ParenthesisRight,
    v_ParenthesisLeft,
    v_At,
    v_Comma,
    v_SemiColon,
    v_Dot,
};

class DelimiterSymbol : public Symbol {

public:
    static int size;
    static std::string stringValues[6];
    DelimiterSymbolEnum keyword;

    explicit DelimiterSymbol(int val) {
        this->symbolValueType = s_Delimiter;
        if (val >= v_ParenthesisRight && val <= v_Dot) {
            this->keyword = static_cast<DelimiterSymbolEnum>(val);
        } else {
            this->keyword = v_ParenthesisRight;
        }
    }

    void display() override {
        printf("Delimiter : %s\n", DelimiterSymbol::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_DELIMITERSYMBOL_H
