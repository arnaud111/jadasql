//
// Created by nono on 19/12/2023.
//

#ifndef JADA_INSERTABLEROW_H
#define JADA_INSERTABLEROW_H

#include <vector>
#include "InsertableField.h"

class InsertableRow {

public:
    std::vector<InsertableField *> listField;

    explicit InsertableRow(std::vector<InsertableField *> listField);

};

#endif //JADA_INSERTABLEROW_H
