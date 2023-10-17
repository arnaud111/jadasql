//
// Created by a833444 on 17/10/2023.
//

#ifndef JADA_LEFTFUNCTION_H
#define JADA_LEFTFUNCTION_H

#include <utility>
#include <vector>
#include "FunctionField.h"
#include "../expression/Expression.h"

class CoalesceFunction : public FunctionField {

public:

    std::vector<Field *> fields;

    explicit CoalesceFunction(std::vector<Field *> fields) {
        this->function = f_Coalesce;
        this->fields = std::move(fields);
    };
};

#endif //JADA_LEFTFUNCTION_H
