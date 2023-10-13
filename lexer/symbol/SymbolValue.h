//
// Created by nono on 11/10/23.
//

#ifndef JADA_SYMBOLVALUE_H
#define JADA_SYMBOLVALUE_H

enum SymbolValueType {
    v_DataType,
    v_Delimiter,
    v_Keyword,
    v_Operator,
    v_Statement,
    v_Number,
    v_String,
    v_None,
};

class SymbolValue {

public:
    SymbolValueType symbolValueType = v_None;
    virtual void display() = 0;

};

#endif //JADA_SYMBOLVALUE_H
