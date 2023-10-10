//
// Created by nono on 10/10/23.
//

#ifndef JADA_SELECTSTATEMENT_H
#define JADA_SELECTSTATEMENT_H

#include <vector>
#include <string>
#include "../from/From.h"
#include "../condition/Condition.h"

class SelectStatement {
    std::vector<std::string> field;
    From from;
    Condition where;
    int limit;
    bool distinct;

};


#endif //JADA_SELECTSTATEMENT_H
