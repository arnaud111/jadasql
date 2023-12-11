//
// Created by nono on 14/11/2023.
//

#ifndef JADA_TIMESTAMP_H
#define JADA_TIMESTAMP_H


#include "DataType.h"

class Timestamp: public DataType {

public:

    explicit Timestamp();

    void display() override;

    ReturnedValue *execute() override;
};


#endif //JADA_TIMESTAMP_H
