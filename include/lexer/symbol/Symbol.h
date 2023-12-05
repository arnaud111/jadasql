//
// Created by nono on 11/10/23.
//

#ifndef JADA_SYMBOL_H
#define JADA_SYMBOL_H

enum SymbolType {
    s_DataType,
    s_Delimiter,
    s_Keyword,
    s_Operator,
    s_Statement,
    s_Number,
    s_String,
    s_Identifier,
    s_None,
};

class Symbol {

public:
    SymbolType symbolValueType = s_None;

    virtual void display() = 0;
};

#endif //JADA_SYMBOL_H
