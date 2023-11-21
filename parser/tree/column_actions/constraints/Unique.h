//
// Created by nono on 21/11/2023.
//

#ifndef JADA_UNIQUE_H
#define JADA_UNIQUE_H

#include "../ColumnConstraints.h"
#include "../../structure/ColumnReference.h"

class Unique: public ColumnConstraints {

public:

    std::vector<ColumnReference *> columns;

    explicit Unique(std::vector<Symbol *> symbols);

    void display() override;

};

#endif //JADA_UNIQUE_H
