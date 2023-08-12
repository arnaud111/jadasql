//
// Created by a833444 on 07/08/2023.
//

#ifndef JADA_FROMCLAUSE_H
#define JADA_FROMCLAUSE_H

#include <vector>
#include "../structure/Table.h"
#include "../../list/List.h"
#include "../joint/Joint.h"

class FromClause {
    Table table;
    vector<Joint> jointList;
};

#endif //JADA_FROMCLAUSE_H
