//
// Created by nono on 14/11/2023.
//

#ifndef JADA_PRIMARYKEY_H
#define JADA_PRIMARYKEY_H

#include <vector>
#include "../ColumnConstraints.h"
#include "../../field/Field.h"

class PrimaryKey: public ColumnConstraints {

public:

    std::vector<Field *> columns;

    explicit PrimaryKey(std::vector<Symbol *> symbols);

};

#endif //JADA_PRIMARYKEY_H
