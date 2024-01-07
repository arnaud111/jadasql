//
// Created by nono on 19/12/2023.
//

#ifndef JADA_INSERTABLEFIELD_H
#define JADA_INSERTABLEFIELD_H

#include "parser/tree/datatype/DataType.h"
#include "parser/tree/field/Field.h"

class InsertableField {

public:
    DataType *dataType;
    Field *value;

    explicit InsertableField(DataType *dataType, Field *value);

    const char *to_writable();

    int size_of();
};

#endif //JADA_INSERTABLEFIELD_H
