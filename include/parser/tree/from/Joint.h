//
// Created by nono on 16/10/2023.
//

#ifndef JADA_JOINT_H
#define JADA_JOINT_H

#include "../structure/TableReference.h"
#include "../operation/Operation.h"

enum JointTypeEnum {
    InnerJoin,
    LeftJoin,
    RightJoin,
};

class Joint : public TreeItem {

public:
    JointTypeEnum joinType;
    TableReference *table;
    Field *on;

    void display() override;

    ReturnedValue *execute() override;

    explicit Joint(std::vector<Symbol *> symbols);
};

#endif //JADA_JOINT_H
