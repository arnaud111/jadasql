//
// Created by nono on 14/11/2023.
//

#ifndef JADA_DATE_H
#define JADA_DATE_H


#include "DataType.h"

class Date: public DataType {

public:

    explicit Date();

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};


#endif //JADA_DATE_H
