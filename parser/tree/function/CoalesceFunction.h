//
// Created by nono on 17/10/2023.
//

#ifndef JADA_COALESCEFUNCTION_H
#define JADA_COALESCEFUNCTION_H

#include <utility>
#include <vector>
#include "Function.h"

class CoalesceFunction : public Function {

public:

    std::vector<Field *> fields;

    explicit CoalesceFunction(std::vector<Field *> fields) {
        this->function = f_Coalesce;
        this->fields = std::move(fields);
    };

    void display() override;
};

#endif //JADA_COALESCEFUNCTION_H
