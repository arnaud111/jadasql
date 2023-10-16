//
// Created by nono on 10/10/23.
//

#ifndef JADA_FROM_H
#define JADA_FROM_H

#include <vector>
#include "../../../lexer/symbol/Symbol.h"
#include "../structure/TableReference.h"
#include "Joint.h"

class From {

public:
    TableReference *table;
    std::vector<Joint *> listJoint;

    explicit From(const std::vector<Symbol *> &symbols);

private:
    static TableReference *getTableReference(const std::vector<Symbol *> &symbols);
};

#endif //JADA_FROM_H
