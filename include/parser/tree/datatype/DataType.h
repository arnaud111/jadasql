//
// Created by nono on 14/11/2023.
//

#ifndef JADA_DATATYPE_H
#define JADA_DATATYPE_H

#include <vector>
#include "../../../lexer/symbol/Symbol.h"
#include "../tree_item/TreeItem.h"
#include "parser/tree/field/Field.h"

enum DataTypeEnum {
    d_Boolean,
    d_Char,
    d_Date,
    d_DateTime,
    d_Double,
    d_Float,
    d_Int,
    d_Timestamp,
    d_TinyInt,
    d_VarChar,
};

class DataType: public TreeItem {

public:
    DataTypeEnum type;
    int size;

    static DataType *convertToDataType(std::vector<Symbol *> symbols);

    virtual Field *readFromFile(std::ifstream *file) = 0;
};


#endif //JADA_DATATYPE_H
