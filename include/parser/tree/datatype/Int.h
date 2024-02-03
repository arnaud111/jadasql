//
// Created by nono on 14/11/2023.
//

#ifndef JADA_INT_H
#define JADA_INT_H


#include "DataType.h"

class Int: public DataType {

public:

    explicit Int();

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

    Field *readFromFile(std::ifstream *file) override;
};


#endif //JADA_INT_H
