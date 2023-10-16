//
// Created by nono on 12/10/23.
//

#ifndef JADA_KEYWORDSYMBOL_H
#define JADA_KEYWORDSYMBOL_H

#include <string>
#include "../Symbol.h"

enum KeywordSymbolEnum {
    v_From,
    v_Where,
    v_Distinct,
    v_As,
    v_And,
    v_Or,
    v_Not,
    v_Null,
    v_Set,
    v_Limit,
    v_Like,
    v_In,
    v_Between,
    v_Join,
    v_On,
    v_Union,
    v_Having,
    v_Exists,
    v_Any,
    v_All,
    v_Case,
    v_When,
    v_Then,
    v_Else,
    v_End,
    v_Some,
    v_Into,
    v_Database,
    v_Table,
    v_Unique,
    v_Primary,
    v_Foreign,
    v_Key,
    v_Check,
    v_Default,
    v_Index,
    v_Is,
    v_Order,
    v_By,
    v_Inner,
    v_Left,
    v_Right,
    v_Cross,
    v_Group,
    v_Max,
    v_Sum,
    v_Count,
    v_Concat,
    v_Format,
    v_Min,
    v_Avg,
    v_IfNull,
    v_Coalesce,
};

class KeywordSymbol: public Symbol {

public:
    static int size;
    static std::string stringValues[55];
    KeywordSymbolEnum keyword;

    explicit KeywordSymbol(int val) {
        this->symbolValueType = s_Keyword;
        if (val >= v_From && val <= v_Coalesce) {
            this->keyword = static_cast<KeywordSymbolEnum>(val);
        } else {
            this->keyword = v_From;
        }
    }

    void display() override {
        printf("Keyword : %s\n", KeywordSymbol::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_KEYWORDSYMBOL_H
