//
// Created by nono on 17/10/2023.
//

#ifndef JADA_TREEITEM_H
#define JADA_TREEITEM_H

#include "interpreter/ReturnedValue.h"
#include "interpreter/ExecutionData.h"

class TreeItem {

public:
    virtual void display() = 0;

    virtual ReturnedValue *execute(ExecutionData *executionData) = 0;
};

#endif //JADA_TREEITEM_H
