//
// Created by nono on 11/10/23.
//

#ifndef JADA_DATATYPEKEYWORD_H
#define JADA_DATATYPEKEYWORD_H

#include "../SymbolValue.h"
#include <vector>
#include <string>

enum DataTypeKeywordEnum {
    Char,
    Varchar,
    Tinyint,
    Boolean,
    Int,
    Float,
    Double,
    Date,
    Datetime,
    Timestamp,
};

class DataTypeKeyword: public SymbolValue {

public:
    static int size;
    static std::string stringValues[10];
    DataTypeKeywordEnum keyword;

    explicit DataTypeKeyword(int val) {
        this->symbolValueType = v_DataType;
        if (val >= Char && val <= Timestamp) {
            this->keyword = static_cast<DataTypeKeywordEnum>(val);
        } else {
            this->keyword = Char;
        }
    }

    void display() override {
        printf("Data Type : %s\n", DataTypeKeyword::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_DATATYPEKEYWORD_H
