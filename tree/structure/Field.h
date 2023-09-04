//
// Created by arnaud on 07/08/2023.
//

#ifndef JADA_FIELD_H
#define JADA_FIELD_H

#include <string>
#include <utility>
#include "Table.h"

using namespace std;

class Field {
    Table table;
    string field;

public:

    Field(string field) {
        this->field = std::move(field);
    }
};

#endif //JADA_FIELD_H
