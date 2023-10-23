//
// Created by nono on 17/10/2023.
//

#ifndef JADA_CONCATFUNCTION_H
#define JADA_CONCATFUNCTION_H

#include <utility>
#include <vector>
#include "Function.h"
#include "../expression/Expression.h"

class ConcatFunction : public Function {

public:

    std::vector<Field *> fields;

    explicit ConcatFunction(std::vector<Field *> fields) {
        this->function = f_Concat;
        this->fields = std::move(fields);
    };

    void display() override;
};

#endif //JADA_CONCATFUNCTION_H
