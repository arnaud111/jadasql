//
// Created by nono on 11/10/23.
//

#ifndef JADA_DATATYPESYMBOL_H
#define JADA_DATATYPESYMBOL_H

#include "../Symbol.h"
#include <vector>
#include <string>

enum DataTypeSymbolEnum {
    v_Char,
    v_Varchar,
    v_Tinyint,
    v_Boolean,
    v_Int,
    v_Float,
    v_Double,
    v_Date,
    v_Datetime,
    v_Timestamp,
};

class DataTypeSymbol : public Symbol {

public:
    static int size;
    static std::string stringValues[10];
    DataTypeSymbolEnum keyword;

    explicit DataTypeSymbol(int val) {
        this->symbolValueType = s_DataType;
        if (val >= v_Char && val <= v_Timestamp) {
            this->keyword = static_cast<DataTypeSymbolEnum>(val);
        } else {
            this->keyword = v_Char;
        }
    }

    void display() override {
        printf("Data Type : %s\n", DataTypeSymbol::stringValues[this->keyword].c_str());
    }
};

#endif //JADA_DATATYPESYMBOL_H
