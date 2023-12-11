//
// Created by nono on 17/10/2023.
//

#ifndef JADA_TREEITEM_H
#define JADA_TREEITEM_H

#include "interpreter/ReturnedValue.h"

class TreeItem {

public:
    virtual void display() = 0;

    virtual ReturnedValue *execute() = 0;
};

#endif //JADA_TREEITEM_H
