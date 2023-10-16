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

class Joint {

public:
    JointTypeEnum joinType;
    TableReference* table;
    Condition* on;
};

#endif //JADA_JOINT_H
