//
// Created by nono on 14/11/2023.
//

#ifndef JADA_CHAR_H
#define JADA_CHAR_H


#include "DataType.h"

class Char: public DataType {

public:

    unsigned long long size;

    explicit Char(std::vector<Symbol *> symbol);

    void display() override;
};


#endif //JADA_CHAR_H
