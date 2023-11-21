//
// Created by nono on 14/11/2023.
//

#ifndef JADA_COLUMNDETAIL_H
#define JADA_COLUMNDETAIL_H


#include "../structure/ColumnReference.h"
#include "../datatype/DataType.h"
#include "ColumnCreationInfo.h"

class ColumnDetail: public ColumnCreationInfo {

public:
    ColumnReference *name;
    DataType *dataType;
    bool autoIncrement;
    bool notNull;
    Field *defaultValue;

    explicit ColumnDetail(std::vector<Symbol *> symbols);

    void display() override;
};


#endif //JADA_COLUMNDETAIL_H
