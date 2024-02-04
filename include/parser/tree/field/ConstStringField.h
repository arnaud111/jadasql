//
// Created by nono on 17/10/2023.
//

#ifndef JADA_CONSTSTRINGFIELD_H
#define JADA_CONSTSTRINGFIELD_H

#include <string>
#include <utility>
#include "Field.h"

class ConstStringField: public Field {

public:

    std::string value;

    explicit ConstStringField(std::string value) {
        this->value = std::move(value);
        this->fieldType = f_ConstString;
    }

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

    ReturnedValue *execute() const;
};

#endif //JADA_CONSTSTRINGFIELD_H
