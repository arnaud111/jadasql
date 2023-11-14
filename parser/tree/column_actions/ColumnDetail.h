//
// Created by nono on 14/11/2023.
//

#ifndef JADA_COLUMNDETAIL_H
#define JADA_COLUMNDETAIL_H


#include "../tree_item/TreeItem.h"
#include "../structure/ColumnReference.h"
#include "../datatype/DataType.h"

class ColumnDetail: public TreeItem {

public:
    ColumnReference *name;
    DataType *dataType;
    bool unique;
    bool notNull;
    Field *defaultValue;

    explicit ColumnDetail(std::vector<Symbol *> symbols);
};


#endif //JADA_COLUMNDETAIL_H
