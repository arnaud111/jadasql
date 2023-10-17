//
// Created by nono on 10/10/23.
//

#ifndef JADA_EXPRESSION_H
#define JADA_EXPRESSION_H

#include "../tree_item/TreeItem.h"

class Expression : public TreeItem {
    virtual bool evaluate() = 0;
};

#endif //JADA_EXPRESSION_H
