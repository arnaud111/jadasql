//
// Created by nono on 14/11/2023.
//

#ifndef JADA_VARCHAR_H
#define JADA_VARCHAR_H


#include "DataType.h"

class VarChar: public DataType {

public:

    unsigned long long size;

    explicit VarChar(std::vector<Symbol *> symbol);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};


#endif //JADA_VARCHAR_H
