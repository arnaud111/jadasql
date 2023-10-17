//
// Created by nono on 16/10/2023.
//

#ifndef JADA_JOINT_H
#define JADA_JOINT_H

#include "../structure/TableReference.h"
#include "../condition/Condition.h"

enum JointTypeEnum {
    Join,
    InnerJoin,
    LeftJoin,
    RightJoin,
};

class Joint : public TreeItem {

public:
    JointTypeEnum joinType;
    TableReference *table;
    Condition *on;

    void display() override;
};

#endif //JADA_JOINT_H
