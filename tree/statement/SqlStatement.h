//
// Created by a833444 on 07/08/2023.
//

#ifndef JADA_SQLSTATEMENT_H
#define JADA_SQLSTATEMENT_H

#include "../target/TargetVal.h"

class SqlStatement: TargetVal {

public:
    virtual void compute() = 0;
};


#endif //JADA_SQLSTATEMENT_H
