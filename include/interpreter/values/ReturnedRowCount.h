//
// Created by nono on 12/12/23.
//

#ifndef JADA_RETURNEDROWCOUNT_H
#define JADA_RETURNEDROWCOUNT_H

#include "../ReturnedValue.h"

class ReturnedRowCount: public ReturnedValue {

public:

    int affected;

    explicit ReturnedRowCount(int affected);

    void display() override;
};

#endif //JADA_RETURNEDROWCOUNT_H
