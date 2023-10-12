//
// Created by nono on 12/10/23.
//

#ifndef JADA_KEYWORD_H
#define JADA_KEYWORD_H

#include <string>
#include "../SymbolValue.h"

enum KeywordEnum {
    From,
    Where,
    As,
    And,
    Or,
    Not,
    Null,
    Set,
    Limit,
    Like,
    In,
    Between,
    Join,
    On,
    Union,
    Having,
    Exists,
    Any,
    All,
    Case,
    When,
    Then,
    Else,
    End,
    Some,
    Into,
    Database,
    Table,
    Unique,
    Primary,
    Foreign,
    Key,
    Check,
    Default,
    Index,
    Is,
    Order,
    By,
    Inner,
    Left,
    Right,
    Cross,
    Group,
    Max,
    Sum,
    Count,
    Concat,
    Format,
    Min,
    Avg,
    IfNull,
    Coalesce,
};

class Keyword: SymbolValue {

public:
    static int size;
    static std::string stringValues[55];
    KeywordEnum keyword;

    explicit Keyword(int val) {
        if (val >= From && val <= Timestamp) {
            this->keyword = static_cast<KeywordEnum>(val);
        } else {
            this->keyword = From;
        }
    }

    void display() override {
        printf("Keyword : %s", Keyword::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_KEYWORD_H
