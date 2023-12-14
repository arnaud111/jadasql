//
// Created by nono on 14/11/2023.
//

#ifndef JADA_DATETIME_H
#define JADA_DATETIME_H


#include "DataType.h"

class DateTime: public DataType {

public:

    explicit DateTime();

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};


#endif //JADA_DATETIME_H
