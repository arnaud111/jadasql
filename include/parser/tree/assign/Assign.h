//
// Created by nono on 14/11/2023.
//

#ifndef JADA_ASSIGN_H
#define JADA_ASSIGN_H


#include "../tree_item/TreeItem.h"
#include "../structure/ColumnReference.h"

class Assign: public TreeItem {

public:
    ColumnReference *column;
    Field *value;

    explicit Assign(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue *execute() override;

    static std::vector<Assign *> convert_to_list_assign(std::vector<Symbol *> symbols);
};


#endif //JADA_ASSIGN_H
