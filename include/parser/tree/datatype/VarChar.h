//
// Created by nono on 14/11/2023.
//

#ifndef JADA_VARCHAR_H
#define JADA_VARCHAR_H


#include "DataType.h"

class VarChar: public DataType {

public:

    explicit VarChar(std::vector<Symbol *> symbol);

    explicit VarChar(int size);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

    Field *readFromFile(std::ifstream *file) override;
};


#endif //JADA_VARCHAR_H
