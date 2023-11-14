//
// Created by nono on 14/11/2023.
//

#ifndef JADA_CHECK_H
#define JADA_CHECK_H

#include "../ColumnConstraints.h"
#include "../../field/Field.h"

class Check: public ColumnConstraints {

public:
    Field *condition;

    explicit Check(std::vector<Symbol *> symbols);

};

#endif //JADA_CHECK_H
