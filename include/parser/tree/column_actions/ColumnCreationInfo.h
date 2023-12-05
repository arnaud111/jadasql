//
// Created by nono on 21/11/2023.
//

#ifndef JADA_COLUMNCREATIONINFO_H
#define JADA_COLUMNCREATIONINFO_H

#include "../tree_item/TreeItem.h"
#include "../../../lexer/symbol/Symbol.h"

enum ColumnCreationType {
    t_ColumnConstraints,
    t_ColumnDetail,
};

class ColumnCreationInfo: public TreeItem {

public:

    ColumnCreationType columnCreationType;

    static ColumnCreationInfo *convertToColumnCreationInfo(std::vector<Symbol *> symbols);
};


#endif //JADA_COLUMNCREATIONINFO_H
