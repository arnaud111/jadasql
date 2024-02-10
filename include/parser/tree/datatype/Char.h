//
// Created by nono on 14/11/2023.
//

#ifndef JADA_CHAR_H
#define JADA_CHAR_H


#include "DataType.h"

class Char: public DataType {

public:

    explicit Char(std::vector<Symbol *> symbol);

    explicit Char(int size);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;

    Field *readFromFile(std::ifstream *file) override;
};


#endif //JADA_CHAR_H
