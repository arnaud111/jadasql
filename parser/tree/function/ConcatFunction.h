//
// Created by nono on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include <utility>
#include <vector>
#include "FunctionField.h"
#include "../expression/Expression.h"

class ConcatFunction : public FunctionField {

public:

    std::vector<Field *> fields;

    explicit ConcatFunction(std::vector<Field *> fields) {
        this->function = f_Concat;
        this->fields = std::move(fields);
    };
};

#endif //JADA_LEFTFUNCTION_H
