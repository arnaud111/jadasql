//
// Created by nono on 14/11/2023.
//

#ifndef JADA_TINYINT_H
#define JADA_TINYINT_H


#include "DataType.h"

class TinyInt: public DataType {

public:

    explicit TinyInt();

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

    Field *readFromFile(std::ifstream *file) override;
};


#endif //JADA_TINYINT_H
