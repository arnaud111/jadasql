//
// Created by a833444 on 17/10/2023.
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
};

#endif //JADA_CONSTSTRINGFIELD_H
