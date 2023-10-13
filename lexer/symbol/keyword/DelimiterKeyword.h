//
// Created by nono on 11/10/23.
//

#ifndef JADA_DELIMITERKEYWORD_H
#define JADA_DELIMITERKEYWORD_H

#include "../SymbolValue.h"
#include <string>

enum DelimiterKeywordEnum {
    ParenthesisRight,
    ParenthesisLeft,
    Comma,
    SemiColon,
    Dot,
};

class DelimiterKeyword: public SymbolValue {

public:
    static int size;
    static std::string stringValues[5];
    DelimiterKeywordEnum keyword;

    explicit DelimiterKeyword(int val) {
        this->symbolValueType = v_Delimiter;
        if (val >= ParenthesisRight && val <= Dot) {
            this->keyword = static_cast<DelimiterKeywordEnum>(val);
        } else {
            this->keyword = ParenthesisRight;
        }
    }

    void display() override {
        printf("Delimiter : %s\n", DelimiterKeyword::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_DELIMITERKEYWORD_H
