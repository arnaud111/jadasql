//
// Created by nono on 13/11/2023.
//

#ifndef JADA_COLUMNMODIFICATION_H
#define JADA_COLUMNMODIFICATION_H


#include "../tree_item/TreeItem.h"
#include "../structure/ColumnReference.h"
#include "../datatype/DataType.h"

enum ModificationType {
    m_Add,
    m_Drop,
    m_Modify,
    m_Change,
};

class ColumnModification: public TreeItem {

public:

    ModificationType modificationType;
    ColumnReference *columnReference;
    DataType *dataType;
    ColumnReference *renameValue;

    explicit ColumnModification(std::vector<Symbol *> symbols);

    void display() override;
};


#endif //JADA_COLUMNMODIFICATION_H
