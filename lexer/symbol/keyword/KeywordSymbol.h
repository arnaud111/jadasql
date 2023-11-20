//
// Created by nono on 12/10/23.
//

#ifndef JADA_KEYWORDSYMBOL_H
#define JADA_KEYWORDSYMBOL_H

#include <string>
#include "../Symbol.h"

enum KeywordSymbolEnum {
    k_From,
    k_Values,
    k_Where,
    k_Distinct,
    k_As,
    k_If,
    k_And,
    k_Or,
    k_Not,
    k_Null,
    k_Set,
    k_Limit,
    k_Like,
    k_In,
    k_Between,
    k_Join,
    k_On,
    k_Union,
    k_Having,
    k_Exists,
    k_Any,
    k_All,
    k_Case,
    k_When,
    k_Then,
    k_Else,
    k_End,
    k_Some,
    k_Into,
    k_Modify,
    k_Change,
    k_Add,
    k_Database,
    k_Table,
    k_Unique,
    k_Primary,
    k_Foreign,
    k_Key,
    k_Check,
    k_Default,
    k_Index,
    k_Is,
    k_Order,
    k_By,
    k_Asc,
    k_Desc,
    k_Inner,
    k_Left,
    k_Right,
    k_Cross,
    k_Group,
    k_Max,
    k_Sum,
    k_Count,
    k_Concat,
    k_Format,
    k_Min,
    k_Avg,
    k_IfNull,
    k_Coalesce,
};

class KeywordSymbol : public Symbol {

public:
    static int size;
    static std::string stringValues[62];
    KeywordSymbolEnum keyword;

    explicit KeywordSymbol(int val) {
        this->symbolValueType = s_Keyword;
        if (val >= k_From && val <= k_Coalesce) {
            this->keyword = static_cast<KeywordSymbolEnum>(val);
        } else {
            this->keyword = k_From;
        }
    }

    void display() override {
        printf("Keyword : %s\n", KeywordSymbol::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_KEYWORDSYMBOL_H
