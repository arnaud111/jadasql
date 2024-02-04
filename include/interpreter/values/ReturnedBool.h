//
// Created by nono on 04/02/24.
//

#ifndef JADA_RETURNEDBOOL_H
#define JADA_RETURNEDBOOL_H

#include "../ReturnedValue.h"

class ReturnedBool: public ReturnedValue {

public:

    bool value;

    explicit ReturnedBool(bool value);

    void display() override;
};

#endif //JADA_RETURNEDBOOL_H
