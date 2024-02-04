//
// Created by nono on 04/02/24.
//

#ifndef JADA_RETURNEDNUMBER_H
#define JADA_RETURNEDNUMBER_H

#include "../ReturnedValue.h"

class ReturnedNumber: public ReturnedValue {

public:

    int value;

    explicit ReturnedNumber(int value);

    void display() override;
};

#endif //JADA_RETURNEDNUMBER_H
