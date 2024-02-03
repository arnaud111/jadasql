//
// Created by nono on 14/11/2023.
//

#ifndef JADA_DOUBLE_H
#define JADA_DOUBLE_H


#include "DataType.h"

class Double: public DataType {

public:

    explicit Double();

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

    Field *readFromFile(std::ifstream *file) override;
};


#endif //JADA_DOUBLE_H
