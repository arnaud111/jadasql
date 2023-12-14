//
// Created by nono on 10/10/23.
//

#ifndef JADA_FROM_H
#define JADA_FROM_H

#include <vector>
#include "../../../lexer/symbol/Symbol.h"
#include "../structure/TableReference.h"
#include "Joint.h"

class From : public TreeItem {

public:
    TableReference *table;
    std::vector<Joint *> listJoint;

    explicit From(const std::vector<Symbol *> &symbols);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_FROM_H
