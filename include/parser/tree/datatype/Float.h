//
// Created by nono on 14/11/2023.
//

#ifndef JADA_FLOAT_H
#define JADA_FLOAT_H


#include "DataType.h"

class Float: public DataType {

public:

    explicit Float();

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};


#endif //JADA_FLOAT_H
